# My Portfolio

A personal portfolio application for **Rajkumar**, a B.E. Computer Science Engineering student and full-stack developer.

The project is moving from a static HTML/CSS/JS site to a **native Linux desktop app written in C, using GTK4 for the UI and GTK's CSS support for styling** — same content (home, education & skills, projects, internships, about, contact, light/dark theme), rebuilt as a real GTK application instead of a browser page. The existing `src/*.html` prototype stays in the repo for reference while the GTK rewrite lands.

This README intentionally stays high-level. It does not explain the application's own C source — the point of rewriting this as a GTK app is to have real, readable GTK code to study, so the source is left to speak for itself. What *is* documented thoroughly, in [`docs/`](docs/), is everything about GTK and the build/dev environment you need to read that code comfortably: how to install GTK4 and the toolchain, how the project is laid out, how GTK CSS theming works, and where to go in the official GTK docs for anything not covered here.

## Quick start

```bash
# Debian/Ubuntu — see docs/getting-started.md for other distros
sudo apt install build-essential meson ninja-build pkg-config libgtk-4-dev

meson setup build
ninja -C build
./build/src/my-portfolio
```

See [docs/getting-started.md](docs/getting-started.md) for per-distro dependency install commands, alternative build methods, and how to run the GTK Inspector against the app.

## Documentation

Further documentation lives in [`docs/`](docs/), starting at [`docs/README.md`](docs/README.md):

- [Getting started](docs/getting-started.md) — installing GTK4 + the toolchain, building, running, and using the GTK Inspector to study the app live.
- [Application structure](docs/site-structure.md) — how the GTK app's sources, resources, and the legacy HTML prototype are organized.
- [Theming](docs/theming.md) — how GTK CSS and the light/dark toggle work, with pointers into the official GTK CSS reference.
- [Customization](docs/customization.md) — editing nav items, colors, and contact info without needing to read the whole codebase first.
- [Project writeups](docs/project-writeups/) — standalone writeups for individual projects featured in the app.

## License

Apache License 2.0 — see [LICENSE](LICENSE).
