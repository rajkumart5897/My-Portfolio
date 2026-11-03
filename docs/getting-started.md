# Getting Started

This is a static site — no installation or build process is required.

## Option 1: Open directly

Open `src/home.html` in your browser.

## Option 2: Serve locally (recommended)

Serving over HTTP avoids any browser restrictions on local file access and more closely matches production:

```bash
cd src
python3 -m http.server 8000
```

Then visit `http://localhost:8000/home.html`.

## Deployment

Because the site is fully static, it can be hosted on any static file host (GitHub Pages, Netlify, Vercel, etc.) by pointing the host at the `src/` directory, with `home.html` set as the index page (or renamed to `index.html` for hosts that require it).

See [site-structure.md](site-structure.md) for how the pages and assets are organized, and [customization.md](customization.md) for how to adapt the site.
