# Implementation Plan (`linux-src/`)

The GTK app is built incrementally, one stage at a time, each stage landing a
working binary rather than a pile of unfinished scaffolding. This doc tracks
the architecture those stages build toward and which stage the app is
currently at.

## Architecture: modular monolith

The app ships as a single binary (no plugins, no IPC between pieces — a
monolith), but internally it's cut into small, independently-readable modules
with their own header and `.c` file, each owning one responsibility and
exposing only what other modules need through its header. Nothing is wired
together with loose `GtkBuilder` `.ui` files and string-based
`gtk_builder_get_object()` lookups — every widget that has behavior is its own
`GObject` type (`G_DECLARE_FINAL_TYPE` + `G_DEFINE_TYPE`), constructed and
composed in C, with a real public API:

```
linux-src/
├── meson.build
├── main.c                        # Entry point: builds & runs PortfolioApplication
├── nav.c/.h                      # PortfolioNav : GtkBox — sidebar page list, shared by every page
├── core/
│   ├── portfolio-application.c/.h   # PortfolioApplication : GtkApplication — app-level lifecycle
│   └── portfolio-window.c/.h        # PortfolioWindow : GtkApplicationWindow — composition root
├── ui/
│   ├── pages/                    # One GObject widget type per page
│   │   ├── portfolio-home-page.c/.h
│   │   ├── portfolio-ed-skills-page.c/.h
│   │   ├── portfolio-projects-page.c/.h
│   │   ├── portfolio-internships-page.c/.h
│   │   ├── portfolio-about-page.c/.h
│   │   └── portfolio-contact-page.c/.h
│   └── widgets/                  # Small reusable widgets, each its own module
│       ├── portfolio-stat-strip.c/.h
│       └── portfolio-feature-card.c/.h
└── resources/
    ├── style.css
    ├── portrait.jpg
    └── portfolio.gresource.xml
```

Module boundaries:

- **`core/`** — app bootstrapping and the top-level window. `portfolio-window.c`
  is the *composition root*: it's the one place that knows about every page
  and widget module and wires them together. Pages and widgets never reach
  back up into `core/`.
- **`ui/widgets/`** — small, content-agnostic pieces (a stat strip, a feature
  card) that take their data through constructor arguments / setters and know
  nothing about where they're used. Reused across pages once more than one
  page needs the same shape of thing.
- **`ui/pages/`** — one module per page (home, about, projects, …), each a
  `GtkBox` subclass that lays out that page's content using the widgets above
  plus plain `GtkLabel`/`GtkBox` for one-off content. A page module never
  reaches into another page.
- **`resources/`** — `style.css` (GTK CSS, see [theming.md](theming.md)) and
  binary assets, bundled into the binary as a `GResource` rather than read
  from disk at runtime.

This keeps each file small enough to read end-to-end, keeps styling classes
and widget names declared next to the widget that uses them, and means a
later stage (e.g. adding the sidebar nav) touches `core/portfolio-window.c`
and adds new files, rather than editing a monolithic `main.c`.

## Stages

Each stage is a separate, working milestone. Later stages are sketched at the
level this plan can commit to today; they'll be refined into their own
sections as they're reached.

| Stage | Scope | Status |
|-------|-------|--------|
| **1** | Home page: hero, "at a glance" stats, featured work, about teaser — with its full styling (`style.css`), as a standalone window. No sidebar nav yet; the window hosts the home page directly. | **Done** — see below |
| **2** | Sidebar navigation (`nav.c`) + `GtkStack`, so the window can hold more than one page | **Done** — see below |
| **3** | Remaining pages: Education & Skills, Projects, Internships, About, Contact | **Done** — see below |
| 4 | Light/dark theme toggle (`theme.c`), persisted across runs | Planned |
| 5 | App icon, `.desktop` file, `ninja install` / packaging notes | Planned |

### Stage 1 — Home page

Implements the GTK equivalent of `web-src/Index.html`'s `<main>` content:

- Hero: eyebrow line, heading, role line, intro paragraph, portrait image,
  and a button row ("View projects" / "Download resume" — inert in this
  stage, since the pages and file they'd link to don't exist yet).
- "At a glance" stat strip: a reusable `PortfolioStatStrip` widget holding
  four `PortfolioStatStrip` entries (Projects, Internships, Technologies,
  Expected graduation), mirroring `.stat-strip` in `web-src/styles.css`.
- "Featured work": three `PortfolioFeatureCard` widgets (Hardware-Compat,
  ScamDetect, Personal Task Tracker) in the same wide-plus-two-narrow layout
  as `.feature-grid`.
- "About" teaser paragraph.

Styling lives in `resources/style.css`, using the same color tokens as
`web-src/styles.css` (re-declared as GTK `@define-color` values — GTK CSS has
no CSS custom properties, see [theming.md](theming.md)) so both builds read
as the same design. Stage 1 ships one fixed (light) palette; the light/dark
toggle itself is Stage 4.

Run it with:

```bash
meson setup build
ninja -C build
./build/linux-src/my-portfolio
```

### Stage 2 — Sidebar navigation

`nav.c` adds `PortfolioNav`, a `GtkBox` holding a brand header ("RK" mark +
"Rajkumar", mirroring `web-src`'s `.brand`) and a `GtkListBox` built from one
fixed `NAV_ITEMS` array — same six labels and order as `web-src`'s
`<ul class="nav-links">`: Home, Education & Skills, Projects, Internships,
About, Contact. It knows nothing about page content, only each row's label
and the `GtkStack` child name it maps to; selecting a row emits its own
`"page-selected"` signal carrying that name.

`core/portfolio-window.c` is the only listener. Stage 1's single `home_page`
child is replaced with a horizontal `GtkBox` holding the nav sidebar and a
`GtkStack` (each page wrapped in its own `GtkScrolledWindow`, so the sidebar
stays fixed while a page's own content scrolls — `web-src`'s `<nav>` is
likewise a sibling of `<main>`, not inside it). The window connects
`"page-selected"` to `gtk_stack_set_visible_child_name()`, then calls
`portfolio_nav_select_home()` once to select "Home" and fire the first
selection, so the stack's initial page and the nav's selected row agree.

A GTK desktop app conventionally puts primary navigation down the side
rather than across the top like `web-src`'s `<nav class="site-nav">` — see
[customization.md](customization.md) — so Stage 2 is a sidebar, not a
pixel-for-pixel copy of the HTML nav bar's chrome. The set of destinations it
reaches is 1:1 with it.

Styling additions: `.portfolio-nav`, `.nav-brand`, `.nav-row` (with
`:selected`/`:hover` states using `@accent_soft_color`, mirroring the active
link highlight in `web-src/styles.css`), and `.nav-separator`.

### Stage 3 — Remaining pages

Five more `ui/pages/` modules, each mirroring its `web-src/*.html`
counterpart's `<main>` content:

- **`portfolio-ed-skills-page.c`** — two `GtkGrid` "tables" (Education; Core
  competencies), each row built from a small static data array.
- **`portfolio-projects-page.c`** — intro (eyebrow/heading/body) plus every
  project from `web-src/projects.html` as a `PortfolioFeatureCard`, reusing
  the same widget the home page's "Featured work" section uses.
- **`portfolio-internships-page.c`** — the same "this page is being written"
  empty state as `web-src/internships.html`; the two internships' content
  hasn't been written on either build yet.
- **`portfolio-about-page.c`** — a hero (reusing the same `portrait.jpg`
  resource as the home page — `web-src`'s `Index.html` and `about.html` use
  the same photo), a "Journey" timeline, and an "Interests" tag row.
- **`portfolio-contact-page.c`** — GitHub/LinkedIn/email rows as
  `GtkLinkButton`s, same placeholder values as `web-src/contacts.html` (see
  [customization.md](customization.md) for replacing them with real ones).

`core/portfolio-window.c` registers all five as named `GtkStack` children
alongside `"home"`. Styling additions: `.skills-table*`, `.empty-state*`,
`.about-heading`, `.timeline-item`, `.tag-pill`, and `.contact-row*` in
`resources/style.css`, built from the same color tokens as Stage 1.
