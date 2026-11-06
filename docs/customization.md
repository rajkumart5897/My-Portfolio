# Customization

Common tweaks you can make without reading through the whole codebase first — see [theming.md](theming.md) and [site-structure.md](site-structure.md) for the background on how each of these pieces works.

- **Colors & theme tokens** — edit the `@define-color` declarations at the top of `resources/style.css`. The GTK Inspector (`GTK_DEBUG=interactive`, see [getting-started.md](getting-started.md)) lets you try color changes live before editing the file.
- **Navigation items** — the sidebar is built from one list in `nav.c`, rather than duplicated markup per page like the old HTML version; add, remove, or reorder pages there and the corresponding `GtkStack` page in `app-window.c` picks it up.
- **Contact details** — `src/pages/contact.c` has placeholder strings for LinkedIn and email that should be filled in with real values.
- **Resume** — the "Download resume" action should point at a `Rajkumar_resume.pdf` bundled via `resources/portfolio.gresource.xml` (or opened from a fixed path on disk), replacing the old direct link to `Rajkumar_resume.pdf` next to the HTML files.
- **App ID / window title** — set once in `main.c` where the `GtkApplication` is constructed.
