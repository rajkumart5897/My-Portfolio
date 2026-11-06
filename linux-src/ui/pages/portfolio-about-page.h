#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ABOUT_PAGE (portfolio_about_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioAboutPage, portfolio_about_page, PORTFOLIO, ABOUT_PAGE, GtkBox)

/* About: hero intro, journey timeline, interest tags. Mirrors
 * web-src/about.html's <main>; reuses the same portrait resource as the
 * home page hero (web-src's about.html and Index.html use the same
 * photo too). Takes no arguments. */

GtkWidget *portfolio_about_page_new (void);

G_END_DECLS
