#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_PROJECTS_PAGE (portfolio_projects_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, PORTFOLIO, PROJECTS_PAGE, GtkBox)

/* Projects: the full project list. Mirrors web-src/projects.html's
 * <main> -- same eyebrow/heading/intro, then every project card in the
 * same order, reusing PortfolioFeatureCard (the same widget the home
 * page's "Featured work" section uses). Takes no arguments. */

GtkWidget *portfolio_projects_page_new (void);

G_END_DECLS
