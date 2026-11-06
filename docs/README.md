# Documentation

This is the documentation for **My Portfolio**, a personal portfolio app for Rajkumar being rebuilt as a native Linux desktop application in **C + GTK4**, styled with GTK's own CSS support. It follows the same layout convention as larger open-source projects such as [Chromium](https://www.chromium.org/chromium-projects/): the root [`README.md`](../README.md) is a short entry point, and everything else lives here.

These docs cover GTK, the build, and the project layout thoroughly, on purpose: the app's own C source is deliberately left undocumented in prose, since reading it directly is the point — it's there to be studied as working GTK example code, not summarized.

## Contents

- [Getting started](getting-started.md) — installing GTK4 and the toolchain per distro, building and running the app, and using the GTK Inspector to explore it live.
- [Application structure](site-structure.md) — how the GTK sources, GResource data, and the legacy HTML prototype are organized.
- [Theming](theming.md) — GTK CSS theming, the light/dark toggle, and where to find the full GTK CSS property reference.
- [Customization](customization.md) — editing nav items, colors, and contact info without needing to trace the whole codebase.
- [Project writeups](project-writeups/) — standalone writeups for individual projects featured in the app.
  - [Hardware Compat](project-writeups/hardware-compat.md) — full writeup for the Hardware-Compat project, also summarized on the Projects page.

---

*This index is intentionally lightweight — open an issue/PR with additions.*
