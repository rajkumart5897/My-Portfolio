# Getting Started

My Portfolio is a native **GTK4** application written in **C**, styled with GTK's own CSS support. This page covers everything needed to get it built, running, and open for study on Linux. It does not explain the app's own `.c`/`.h` files — see the note in [`docs/README.md`](README.md) for why — but it goes deep on GTK itself, since that's what you'll want on hand while reading the source.

## 1. Install dependencies

You need a C compiler, a build system (Meson + Ninja), `pkg-config`, and the GTK4 development package. Pick your distro:

**Debian / Ubuntu / Mint / Pop!_OS**
```bash
sudo apt install build-essential meson ninja-build pkg-config libgtk-4-dev
```

**Fedora**
```bash
sudo dnf install gcc meson ninja-build pkgconf-pkg-config gtk4-devel
```

**Arch / Manjaro**
```bash
sudo pacman -S base-devel meson ninja pkgconf gtk4
```

**openSUSE**
```bash
sudo zypper install gcc meson ninja pkgconf-pkg-config gtk4-devel
```

Confirm GTK4 is visible to `pkg-config` (this is how the build finds its compiler/linker flags):

```bash
pkg-config --modversion gtk4
```

If that prints a version (4.x), you're set. The official per-distro install matrix, kept up to date by the GTK project, is at [gtk.org/docs/installations/linux](https://www.gtk.org/docs/installations/linux/).

## 2. Build

From the repo root:

```bash
meson setup build
ninja -C build
```

`meson setup build` configures an out-of-tree build directory (safe to delete and redo with `rm -rf build`); `ninja -C build` compiles it. Re-running `ninja -C build` after editing source is all you need for incremental rebuilds — no need to re-run `meson setup`.

## 3. Run

```bash
./build/linux-src/my-portfolio
```

## 4. Study it with the GTK Inspector

GTK ships a built-in live inspector — this is the fastest way to connect what you're reading in the source to what's actually on screen: click a widget in the inspector and it highlights the matching C object, browse the live CSS node tree, and edit CSS on the fly without recompiling.

```bash
GTK_DEBUG=interactive ./build/linux-src/my-portfolio
```

or trigger it from any running GTK app with <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>I</kbd> (or <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> for a detached window). Reference: [GTK Inspector docs](https://docs.gtk.org/gtk4/visual_index.html#debugging) and `man gtk4-launch`.

Also useful while studying the code:

- **`gtk4-widget-factory`** — a demo app (ships with GTK, or build it from the GTK source tree) showing every stock widget; good for matching a widget's name in the API docs to what it looks like.
- **`gtk4-demo`** — GTK's own example-code browser, with runnable C source for dozens of small apps side by side with their output.

## 5. Core GTK documentation (read these alongside the source)

| Topic | Link |
|---|---|
| GTK4 API reference (widgets, `GtkApplication`, signals) | [docs.gtk.org/gtk4](https://docs.gtk.org/gtk4/) |
| GTK4 "Getting Started" tutorial (the canonical from-scratch C walkthrough) | [docs.gtk.org/gtk4/getting_started.html](https://docs.gtk.org/gtk4/getting_started.html) |
| GObject (the object system all GTK types are built on — needed to read any GTK C code) | [docs.gtk.org/gobject](https://docs.gtk.org/gobject/) |
| GLib (core data types, main loop, memory/string helpers used throughout) | [docs.gtk.org/glib](https://docs.gtk.org/glib/) |
| GIO (`GAction`, `GApplication`, resources) | [docs.gtk.org/gio](https://docs.gtk.org/gio/) |
| GTK CSS overview | [docs.gtk.org/gtk4/css-overview.html](https://docs.gtk.org/gtk4/css-overview.html) |
| GTK CSS property reference | [docs.gtk.org/gtk4/css-properties.html](https://docs.gtk.org/gtk4/css-properties.html) |
| Pango (text rendering/layout, used by any label/text widget) | [docs.gtk.org/Pango](https://docs.gtk.org/Pango/) |
| GtkBuilder `.ui` XML format | [docs.gtk.org/gtk4/class.Builder.html](https://docs.gtk.org/gtk4/class.Builder.html) |

See [site-structure.md](site-structure.md) for how the app's sources and resources are organized, and [theming.md](theming.md) for how the CSS side specifically works. For adapting nav items, colors, or contact info without digging through the C, see [customization.md](customization.md).

## Deployment note

The app is a native binary, not something you host as static files — the old "point a static host at `web-src/`" deployment path no longer applies. `ninja -C build install` (with an appropriate `--prefix` set at `meson setup` time) installs it like any other Meson/GTK project; packaging as a Flatpak is the usual way to distribute a GTK app to end users, see [docs.flatpak.org](https://docs.flatpak.org/) if that's a direction you want to take it.

## Running the legacy web prototype

The original static site is kept in [`web-src/`](../web-src/) and still runs on its own, with no GTK dependencies:

```bash
cd web-src
python3 -m http.server 8000
```

Then visit `http://localhost:8000/Index.html`. It isn't part of the GTK build and won't be touched further as `linux-src/` takes over.
