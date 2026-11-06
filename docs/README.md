# Documentation

This is the documentation for **My Portfolio**, a personal portfolio app for Rajkumar, built both as a static HTML/CSS/JS site and as a native Linux desktop application in **C + GTK4**, styled with GTK's own CSS support. It follows the same layout convention as larger open-source projects such as [Chromium](https://www.chromium.org/chromium-projects/): the root [`README.md`](../README.md) is a short entry point, and everything else lives here.

These docs cover GTK, the build, and the project layout. The app's own C source isn't narrated in prose here — read it directly alongside the GTK references linked throughout.

## Contents

- [Getting started](getting-started.md) — installing GTK4 and the toolchain per distro, building and running the app, and using the GTK Inspector to explore it live.
- [Application structure](site-structure.md) — how the GTK sources and GResource data, and the HTML site, are organized.
- [Implementation plan](implementation-plan.md) — the GTK app's modular-monolith module layout and the staged order it's being built in.
- [Theming](theming.md) — GTK CSS theming, the light/dark toggle, and where to find the full GTK CSS property reference.
- [Customization](customization.md) — editing nav items, colors, and contact info without needing to trace the whole codebase.
- [Project writeups](project-writeups/) — standalone writeups for individual projects featured in the app.
  - [Hardware Compat](project-writeups/hardware-compat.md) — full writeup for the Hardware-Compat project, also summarized on the Projects page.

---

*This index is intentionally lightweight — open an issue/PR with additions.*
