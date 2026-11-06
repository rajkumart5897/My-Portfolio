# Application Structure

This describes the target layout for the GTK4 rewrite — the pieces listed under `resources/` and the new files in `src/` are what the C rewrite adds. The current static prototype (`Index.html`, `about.html`, `styles.css`, `theme.js`, …) stays exactly where it is today, under `src/`, until the GTK app fully replaces it — the two can coexist in the same directory during the transition.

```
my-portfolio/
├── README.md                       # Project overview, points to docs/
├── meson.build                     # Top-level build definition (new)
├── docs/
│   ├── README.md                   # Documentation index
│   ├── getting-started.md          # Installing GTK4/toolchain, building, running, GTK Inspector
│   ├── site-structure.md           # This file
│   ├── theming.md                  # GTK CSS theming and the light/dark toggle
│   ├── customization.md            # Editing nav, colors, contact info
│   └── project-writeups/
│       └── hardware-compat.md      # Standalone writeup for the Hardware-Compat project
├── resources/                      # (new) GTK CSS + GResource bundle
│   ├── style.css                   # GTK CSS for the whole app (see theming.md)
│   ├── portfolio.gresource.xml     # GResource manifest bundling style.css + icons into the binary
│   └── icons/                      # App icon + any symbolic icons
├── Public/
│   └── Images/                     # Public-facing copies of site images
└── src/
    ├── main.c                      # (new) Entry point — GtkApplication setup and activation
    ├── app-window.c / .h           # (new) Main GtkApplicationWindow: header bar, sidebar nav, content stack
    ├── nav.c / .h                  # (new) Sidebar/nav model shared by every page
    ├── theme.c / .h                # (new) Light/dark toggle (GtkSettings + CSS classes)
    ├── pages/                      # (new) One .c/.h pair per page, each builds a GtkWidget subtree
    │   ├── home.c / .h
    │   ├── about.c / .h
    │   ├── ed-skills.c / .h
    │   ├── projects.c / .h
    │   ├── internships.c / .h
    │   └── contact.c / .h
    └── Index.html, about.html, ed_skills.html, hardware-compat.html,   # existing static prototype,
        internships.html, projects.html, contacts.html, styles.css,     # kept as-is for reference
        theme.js, Images/                                               # during the transition
```

As with the structure of the sources themselves, this document describes *where things live*, not *how the C works* — reading `src/` directly, alongside the GTK docs linked from [getting-started.md](getting-started.md), is the intended way to learn that part.

## Pages

Each page is one `GtkWidget` subtree built by its own file under `src/pages/`, swapped into a `GtkStack` in `app-window.c` and selected from the sidebar nav built in `nav.c`.

| Page | Source | Description |
|------|--------|--------------|
| Home | `src/pages/home.c` | Intro, at-a-glance stats, featured projects |
| Education & Skills | `src/pages/ed-skills.c` | Education history and core technical competencies |
| Projects | `src/pages/projects.c` | List of projects, linking out to full writeups |
| Hardware-Compat | linked from `src/pages/projects.c` | Full case study for the Hardware-Compat project ([writeup](project-writeups/hardware-compat.md)) |
| Internships | `src/pages/internships.c` | Placeholder — content in progress |
| About | `src/pages/about.c` | Background, journey, and interests |
| Contact | `src/pages/contact.c` | GitHub, LinkedIn, and email links |

Because every page shares one `GtkApplicationWindow` and one sidebar built in `nav.c`, adding or renaming a page means registering it once in `nav.c` rather than editing a `<nav>` block in every file — one of the things that's simpler than the old static-HTML version it replaces.

`resources/` holds everything bundled into the binary via [`GResource`](https://docs.gtk.org/gio/class.Resource.html) — the CSS, and icons. `Public/` still mirrors assets intended for external reference (e.g. for this README on GitHub) outside of the compiled app. The previous static site lives under `src-web-legacy/` purely for reference while the rewrite is in progress; it is not part of the build.
