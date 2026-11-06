# Application Structure

The repo holds two independent builds of the same portfolio, side by side: `linux-src/` is the GTK4 + C desktop app, `web-src/` is the HTML/CSS/JS site. Neither depends on or replaces the other. The pieces under `linux-src/` marked *(planned)* below are what the GTK app still needs — its build system and sources go in incrementally.

```
my-portfolio/
├── README.md                       # Project overview, points to docs/
├── meson.build                     # (planned) Top-level build definition
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
├── linux-src/                      # The GTK4 + C desktop app — see implementation-plan.md for the stage order
│   ├── README.md                   # Points back here — this doc is the source of truth
│   ├── meson.build                 # linux-src build definition: sources, GResource compilation
│   ├── main.c                      # Entry point — builds and runs PortfolioApplication
│   ├── core/
│   │   ├── portfolio-application.c / .h   # PortfolioApplication : GtkApplication
│   │   └── portfolio-window.c / .h        # PortfolioWindow : GtkApplicationWindow — composition root
│   ├── ui/
│   │   ├── pages/                  # One GObject widget type per page
│   │   │   ├── portfolio-home-page.c / .h
│   │   │   ├── about.c / .h        # (planned, Stage 3)
│   │   │   ├── ed-skills.c / .h    # (planned, Stage 3)
│   │   │   ├── projects.c / .h     # (planned, Stage 3)
│   │   │   ├── internships.c / .h  # (planned, Stage 3)
│   │   │   └── contact.c / .h      # (planned, Stage 3)
│   │   └── widgets/                 # Small reusable widgets, each its own module
│   │       ├── portfolio-stat-strip.c / .h
│   │       └── portfolio-feature-card.c / .h
│   ├── nav.c / .h                  # (planned, Stage 2) Sidebar/nav model shared by every page
│   ├── theme.c / .h                # (planned, Stage 4) Light/dark toggle (GtkSettings + CSS classes)
│   └── resources/                  # GTK CSS + GResource bundle
│       ├── style.css               # GTK CSS for the app so far (see theming.md)
│       ├── portrait.jpg            # Home page hero portrait
│       └── portfolio.gresource.xml # GResource manifest bundling style.css + portrait.jpg into the binary
└── web-src/                        # The static HTML/CSS/JS site
    ├── README.md                   # Points back here — this doc is the source of truth
    ├── Index.html, about.html, ed_skills.html, hardware-compat.html,
    │   internships.html, projects.html, contacts.html
    ├── styles.css, theme.js
    └── Images/
```

This document describes *where things live*, not *how the C works*. For the module boundaries and the order modules are being built in, see [implementation-plan.md](implementation-plan.md). For the GTK APIs themselves, see the references linked from [getting-started.md](getting-started.md).

## Pages

Each page is one `GtkWidget` subtree built by its own file under `linux-src/pages/`, swapped into a `GtkStack` in `app-window.c` and selected from the sidebar nav built in `nav.c`.

| Page | Source | Description |
|------|--------|--------------|
| Home | `linux-src/pages/home.c` | Intro, at-a-glance stats, featured projects |
| Education & Skills | `linux-src/pages/ed-skills.c` | Education history and core technical competencies |
| Projects | `linux-src/pages/projects.c` | List of projects, linking out to full writeups |
| Hardware-Compat | linked from `linux-src/pages/projects.c` | Full case study for the Hardware-Compat project ([writeup](project-writeups/hardware-compat.md)) |
| Internships | `linux-src/pages/internships.c` | Placeholder — content in progress |
| About | `linux-src/pages/about.c` | Background, journey, and interests |
| Contact | `linux-src/pages/contact.c` | GitHub, LinkedIn, and email links |

Because every page shares one `GtkApplicationWindow` and one sidebar built in `nav.c`, adding or renaming a page means registering it once in `nav.c` rather than editing a `<nav>` block in every file, which is how `web-src/`'s pages handle navigation.

`linux-src/resources/` holds everything bundled into the binary via [`GResource`](https://docs.gtk.org/gio/class.Resource.html) — the CSS, and icons. `Public/` mirrors assets intended for external reference (e.g. for this README on GitHub) outside of either build. `web-src/` is a complete, independent build of the site on its own; it is not part of the `linux-src/` build and isn't affected by changes there.
