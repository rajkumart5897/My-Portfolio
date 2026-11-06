# Application Structure

The repo holds two independent builds of the same portfolio, side by side: `linux-src/` is the GTK4 + C desktop app, `web-src/` is the HTML/CSS/JS site. Neither depends on or replaces the other. Stage 4 (the light/dark theme toggle) is still *(planned)* — see below.

```
my-portfolio/
├── README.md                       # Project overview, points to docs/
├── docs/
│   ├── README.md                   # Documentation index
│   ├── getting-started.md          # Installing GTK4/toolchain, building, running, GTK Inspector
│   ├── site-structure.md           # This file
│   ├── theming.md                  # GTK CSS theming and the light/dark toggle
│   ├── customization.md            # Editing nav, colors, contact info
│   └── project-writeups/
│       └── hardware-compat.md      # Standalone writeup for the Hardware-Compat project
├── Public/
│   └── Images/                     # Public-facing copies of site images
├── meson.build                      # Root build definition (subdirs into linux-src/)
├── linux-src/                      # The GTK4 + C desktop app
│   ├── README.md                   # Points back here — this doc is the source of truth
│   ├── meson.build                 # linux-src build definition: sources, GResource compilation
│   ├── main.c                      # Entry point — builds and runs PortfolioApplication
│   ├── nav.c / .h                  # Stage 2: sidebar nav model (fixed page list), shared by every page
│   ├── theme.c / .h                # (planned, Stage 4) Light/dark toggle (GtkSettings + CSS classes)
│   ├── core/
│   │   ├── portfolio-application.c / .h   # PortfolioApplication : GtkApplication
│   │   └── portfolio-window.c / .h        # PortfolioWindow : GtkApplicationWindow — composition root (sidebar + GtkStack)
│   ├── ui/
│   │   ├── pages/                  # One GObject widget type per page
│   │   │   ├── portfolio-home-page.c / .h
│   │   │   ├── portfolio-ed-skills-page.c / .h
│   │   │   ├── portfolio-projects-page.c / .h
│   │   │   ├── portfolio-internships-page.c / .h   # Placeholder — content still in progress, same as the HTML site
│   │   │   ├── portfolio-about-page.c / .h
│   │   │   └── portfolio-contact-page.c / .h
│   │   └── widgets/                 # Small reusable widgets, each its own module
│   │       ├── portfolio-stat-strip.c / .h
│   │       └── portfolio-feature-card.c / .h
│   └── resources/                  # GTK CSS + GResource bundle
│       ├── style.css               # GTK CSS for the app so far (see theming.md)
│       ├── portrait.jpg            # Hero portrait, used on both the home and about pages
│       └── portfolio.gresource.xml # GResource manifest bundling style.css + portrait.jpg into the binary
└── web-src/                        # The static HTML/CSS/JS site
    ├── README.md                   # Points back here — this doc is the source of truth
    ├── Index.html, about.html, ed_skills.html, hardware-compat.html,
    │   internships.html, projects.html, contacts.html
    ├── styles.css, theme.js
    └── Images/
```

This document describes *where things live*, not *how the C works*. For the GTK APIs themselves, see the references linked from [getting-started.md](getting-started.md).

## Pages

Each page is one `GtkWidget` subtree built by its own file under `linux-src/ui/pages/`, swapped into a `GtkStack` in `core/portfolio-window.c` and selected from the sidebar nav built in `nav.c`.

| Page | Source | Description |
|------|--------|--------------|
| Home | `linux-src/ui/pages/portfolio-home-page.c` | Intro, at-a-glance stats, featured projects |
| Education & Skills | `linux-src/ui/pages/portfolio-ed-skills-page.c` | Education history and core technical competencies |
| Projects | `linux-src/ui/pages/portfolio-projects-page.c` | List of projects, linking out to GitHub |
| Hardware-Compat | linked from `linux-src/ui/pages/portfolio-projects-page.c` | No local writeup page yet — links out to the GitHub repo, same as the home page's card ([web writeup](project-writeups/hardware-compat.md)) |
| Internships | `linux-src/ui/pages/portfolio-internships-page.c` | Placeholder — content in progress, mirrors web-src's empty state |
| About | `linux-src/ui/pages/portfolio-about-page.c` | Background, journey, and interests |
| Contact | `linux-src/ui/pages/portfolio-contact-page.c` | GitHub, LinkedIn, and email links |

Because every page shares one `GtkApplicationWindow` and one sidebar built in `nav.c`, adding or renaming a page means registering it once in `nav.c`'s `NAV_ITEMS` list and once as a named `GtkStack` child in `core/portfolio-window.c`, rather than editing a `<nav>` block in every file, which is how `web-src/`'s pages handle navigation.

`linux-src/resources/` holds everything bundled into the binary via [`GResource`](https://docs.gtk.org/gio/class.Resource.html) — the CSS, and icons. `Public/` mirrors assets intended for external reference (e.g. for this README on GitHub) outside of either build. `web-src/` is a complete, independent build of the site on its own; it is not part of the `linux-src/` build and isn't affected by changes there.
