# Customization

Common tweaks you can make without reading through the whole codebase first — see [theming.md](theming.md) and [site-structure.md](site-structure.md) for the background on how each of these pieces works. The GTK app (`linux-src/`) and the HTML site (`web-src/`) are separate builds, each with its own copy of this content, so a change to one doesn't automatically apply to the other.

## GTK app (`linux-src/`)

- **Colors & theme tokens** — edit the `@define-color` declarations at the top of `linux-src/resources/style.css`. The GTK Inspector (`GTK_DEBUG=interactive`, see [getting-started.md](getting-started.md)) lets you try color changes live before editing the file.
- **Navigation items** — the sidebar is built from one list (`NAV_ITEMS`) in `linux-src/nav.c`; add, remove, or reorder pages there, and register the matching named child in the `GtkStack` built in `linux-src/core/portfolio-window.c`.
- **Contact details** — `linux-src/pages/contact.c` has placeholder strings for LinkedIn and email that should be filled in with real values.
- **Resume** — the "Download resume" action should point at a `Rajkumar_resume.pdf` bundled via `linux-src/resources/portfolio.gresource.xml` (or opened from a fixed path on disk).
- **App ID / window title** — set once in `linux-src/main.c` where the `GtkApplication` is constructed.

## HTML site (`web-src/`)

- **Colors & theme tokens** — edit the CSS variables at the top of `web-src/styles.css` (`:root` and `:root[data-theme="dark"]`).
- **Navigation links** — the nav bar is duplicated at the top of each HTML file; update all pages together when adding or renaming a page.
- **Contact details** — `web-src/contacts.html` has placeholder links for LinkedIn and email (marked with HTML comments) that should be filled in with real URLs.
- **Resume** — the "Download resume" button links to `Rajkumar_resume.pdf`, which should be placed alongside the HTML files.
