# Theming

`theme.js` handles two things:

1. **Theme toggle** — clicking `.theme-toggle` flips a `data-theme` attribute on `<html>` between `light` and `dark`, and persists the choice to `localStorage` under the `theme` key. On load, a stored preference takes priority; otherwise the site falls back to the visitor's OS-level `prefers-color-scheme`.
2. **Mobile nav** — clicking `.nav-burger` toggles an `open` class on `.nav-links` to show/hide the menu on small screens.

All colors referenced by both themes are defined as CSS custom properties in `styles.css`, under `:root` (light, default) and `:root[data-theme="dark"]` (dark). To adjust the palette, edit these variables rather than individual rules.
