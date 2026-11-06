#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_HOME_PAGE (portfolio_home_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioHomePage, portfolio_home_page, PORTFOLIO, HOME_PAGE, GtkBox)

/* The home page: hero, at-a-glance stats, featured work, about teaser.
 * Mirrors web-src/Index.html's <main>. Takes no arguments — Stage 1's
 * content is fixed; a later stage can add setters if this needs to
 * become data-driven. */

GtkWidget *portfolio_home_page_new (void);

G_END_DECLS
