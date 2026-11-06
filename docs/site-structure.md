# Application Structure

The repo is split into the new GTK4/C app and the old static prototype, side by side: `linux-src/` is where the rewrite lives, `web-src/` is the original HTML/CSS/JS version kept for reference. The pieces under `linux-src/` marked *(planned)* below are what the C rewrite is adding; the build system and sources go in as the rewrite progresses.

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
├── linux-src/                      # The GTK4 + C rewrite
│   ├── README.md                   # Points back here — this doc is the source of truth
│   ├── main.c                      # (planned) Entry point — GtkApplication setup and activation
│   ├── app-window.c / .h           # (planned) Main GtkApplicationWindow: header bar, sidebar nav, content stack
│   ├── nav.c / .h                  # (planned) Sidebar/nav model shared by every page
│   ├── theme.c / .h                # (planned) Light/dark toggle (GtkSettings + CSS classes)
│   ├── pages/                      # (planned) One .c/.h pair per page, each builds a GtkWidget subtree
│   │   ├── home.c / .h
│   │   ├── about.c / .h
│   │   ├── ed-skills.c / .h
│   │   ├── projects.c / .h
│   │   ├── internships.c / .h
│   │   └── contact.c / .h
│   └── resources/                 # (planned) GTK CSS + GResource bundle
│       ├── style.css               # GTK CSS for the whole app (see theming.md)
│       ├── portfolio.gresource.xml # GResource manifest bundling style.css + icons into the binary
│       └── icons/                  # App icon + any symbolic icons
└── web-src/                        # The original static HTML/CSS/JS prototype, kept for reference
    ├── README.md                   # Points back here — this doc is the source of truth
    ├── Index.html, about.html, ed_skills.html, hardware-compat.html,
    │   internships.html, projects.html, contacts.html
    ├── styles.css, theme.js
    └── Images/
```

As with the structure of the sources themselves, this document describes *where things live*, not *how the C works* — reading `linux-src/` directly, alongside the GTK docs linked from [getting-started.md](getting-started.md), is the intended way to learn that part.

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

Because every page shares one `GtkApplicationWindow` and one sidebar built in `nav.c`, adding or renaming a page means registering it once in `nav.c` rather than editing a `<nav>` block in every file — one of the things that's simpler than the `web-src/` version it replaces.

`linux-src/resources/` holds everything bundled into the binary via [`GResource`](https://docs.gtk.org/gio/class.Resource.html) — the CSS, and icons. `Public/` still mirrors assets intended for external reference (e.g. for this README on GitHub) outside of the compiled app. `web-src/` holds the previous static site purely for reference while the rewrite is in progress; it is not part of the `linux-src/` build.
