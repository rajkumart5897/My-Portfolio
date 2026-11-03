# Site Structure

```
my-portfolio/
├── README.md                       # Project overview, points to docs/
├── docs/
│   ├── README.md                   # Documentation index
│   ├── getting-started.md          # Running and deploying the site
│   ├── site-structure.md           # This file
│   ├── theming.md                  # Light/dark toggle and design tokens
│   ├── customization.md            # Editing nav, colors, contact info
│   └── project-writeups/
│       └── hardware-compat.md      # Standalone writeup for the Hardware-Compat project
├── Public/
│   └── Images/                     # Public-facing copies of site images
└── src/
    ├── home.html                   # Landing page
    ├── about.html                  # About / journey / interests
    ├── ed_skills.html              # Education & core competencies
    ├── projects.html               # Project listing
    ├── hardware-compat.html        # Hardware-Compat project case study
    ├── internships.html            # Internships (placeholder — in progress)
    ├── contacts.html                # Contact links
    ├── styles.css                   # Shared design tokens + styles for all pages
    ├── theme.js                     # Theme toggle + nav burger behavior
    └── Images/                      # Images used directly by the HTML pages
```

All source pages live in `src/`, as plain `.html` files sharing one stylesheet (`styles.css`) and one script (`theme.js`).

## Pages

| Page | File | Description |
|------|------|--------------|
| Home | `src/home.html` | Intro, at-a-glance stats, featured projects |
| Education & Skills | `src/ed_skills.html` | Education history and core technical competencies |
| Projects | `src/projects.html` | List of projects, linking out to full writeups |
| Hardware-Compat | `src/hardware-compat.html` | Full case study for the Hardware-Compat project |
| Internships | `src/internships.html` | Placeholder — content in progress |
| About | `src/about.html` | Background, journey, and interests |
| Contact | `src/contacts.html` | GitHub, LinkedIn, and email links |

Each page repeats the same `<nav>` markup, so when adding or renaming a page, update the nav links in every HTML file to keep them in sync.

`Public/` mirrors assets intended for external reference (images) outside of the `src/` build, while `src/Images/` holds the copies actually referenced by the HTML pages. Standalone project writeups live under [`docs/project-writeups/`](project-writeups/).
