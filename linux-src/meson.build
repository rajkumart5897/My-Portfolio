gtk_dep = dependency('gtk4')

gnome = import('gnome')

portfolio_resources = gnome.compile_resources(
  'portfolio-resources',
  'resources/portfolio.gresource.xml',
  source_dir: 'resources',
  c_name: 'portfolio',
)

portfolio_sources = files(
  'main.c',
  'nav.c',
  'theme.c',
  'core/portfolio-application.c',
  'core/portfolio-window.c',
  'ui/pages/portfolio-home-page.c',
  'ui/pages/portfolio-ed-skills-page.c',
  'ui/pages/portfolio-projects-page.c',
  'ui/pages/portfolio-internships-page.c',
  'ui/pages/portfolio-about-page.c',
  'ui/pages/portfolio-contact-page.c',
  'ui/widgets/portfolio-stat-strip.c',
  'ui/widgets/portfolio-feature-card.c',
)

executable(
  'my-portfolio',
  portfolio_sources,
  portfolio_resources,
  dependencies: [gtk_dep],
  install: true,
)
