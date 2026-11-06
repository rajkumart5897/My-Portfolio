# Theming

The app is styled with **GTK's own CSS support** — a real subset of CSS that GTK parses itself and applies to its widget tree. It is not web CSS and not loaded in a browser, but the syntax and cascade/specificity rules will feel familiar if you know CSS. This page explains how theming works in this app; for the full language reference, use the official docs linked at the bottom.

## How it's loaded

`resources/style.css` is bundled into the binary via [`GResource`](https://docs.gtk.org/gio/class.Resource.html) (see [site-structure.md](site-structure.md)) and loaded once at startup, in `theme.c`, with [`GtkCssProvider`](https://docs.gtk.org/gtk4/class.CssProvider.html):

```c
GtkCssProvider *provider = gtk_css_provider_new ();
gtk_css_provider_load_from_resource (provider, "/dev/portfolio/style.css");
gtk_style_context_add_provider_for_display (
    gdk_display_get_default (),
    GTK_STYLE_CONTEXT (provider),
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
```

`GTK_STYLE_PROVIDER_PRIORITY_APPLICATION` means this stylesheet overrides the active system GTK theme's rules where they conflict, but still loses to anything the user forces at a higher priority (e.g. their own `~/.config/gtk-4.0/gtk.css`).

## Selectors: widgets instead of tags

GTK CSS selects on **CSS node names** (roughly: the widget's type, e.g. `button`, `label`, `box`) rather than HTML tags, plus the usual class/id/state selectors:

```css
/* every GtkButton */
button { }

/* a widget with gtk_widget_add_css_class (widget, "nav-item") */
.nav-item { }

/* state, like :hover in web CSS */
button:hover { }

/* a specific named widget (gtk_widget_set_name) */
#sidebar { }

/* descendant combinator works the same as web CSS */
box.sidebar label { }
```

In this app, each page/widget applies its own style classes via `gtk_widget_add_css_class()` (the C-side equivalent of adding a `class="…"` attribute) — grep the source for `add_css_class` to see which class names are in play, then match them up against the selectors in `resources/style.css`.

## Colors and the light/dark toggle

There's no `:root` in GTK CSS. Named colors are declared with `@define-color` and referenced with `@color-name`:

```css
@define-color accent_color #3584e4;
@define-color window_bg_color #fafafa;

button.suggested-action {
  background-color: @accent_color;
}
```

The light/dark toggle in this app (`theme.c`) doesn't swap stylesheets — it flips the [`GtkSettings:gtk-application-prefer-dark-theme`](https://docs.gtk.org/gtk4/property.Settings.gtk-application-prefer-dark-theme.html) property, which tells the active GTK theme (e.g. Adwaita) to switch its own light/dark variant, and persists the choice the same way the old `theme.js` did for the browser version (a value under `~/.config/`, read back on startup). App-specific color overrides in `style.css` can respond to the same state with the `:dir()`-style theme variant selectors GTK themes use internally, but most of this app's own styling (spacing, borders, custom widget classes) is written to look correct in both variants rather than branching per-theme.

## Debugging CSS live

The single most useful tool for understanding how a given rule in `style.css` maps onto the running app is the **GTK Inspector** (see [getting-started.md](getting-started.md)):

```bash
GTK_DEBUG=interactive ./build/linux-src/my-portfolio
```

Select any widget on screen and the inspector shows its full CSS node path and every matching rule with specificity — including rules from the active system theme, not just this app's stylesheet. You can edit CSS directly in the inspector and see it apply instantly, without recompiling.

## Reference

| Topic | Link |
|---|---|
| CSS overview (how GTK's CSS engine works, selectors, cascade) | [docs.gtk.org/gtk4/css-overview.html](https://docs.gtk.org/gtk4/css-overview.html) |
| Full CSS property reference | [docs.gtk.org/gtk4/css-properties.html](https://docs.gtk.org/gtk4/css-properties.html) |
| `GtkCssProvider` | [docs.gtk.org/gtk4/class.CssProvider.html](https://docs.gtk.org/gtk4/class.CssProvider.html) |
| Named/system colors (`@accent_color` etc.) | [docs.gtk.org/gtk4/named-colors.html](https://docs.gtk.org/gtk4/named-colors.html) |
| `gtk_widget_add_css_class` / `_get_css_classes` | [docs.gtk.org/gtk4/method.Widget.add_css_class.html](https://docs.gtk.org/gtk4/method.Widget.add_css_class.html) |
