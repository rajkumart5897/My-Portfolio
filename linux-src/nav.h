#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_NAV (portfolio_nav_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioNav, portfolio_nav, PORTFOLIO, NAV, GtkBox)

/* Stage 2: the sidebar nav. One fixed list of pages, mirroring web-src's
 * <nav class="site-nav"> <ul class="nav-links"> exactly -- same six
 * labels, same order, same destinations. A GTK desktop app conventionally
 * puts this down the side rather than across the top (see
 * docs/customization.md), so the chrome differs from the HTML site, but
 * the set of pages it reaches is 1:1 with it.
 *
 * Content-agnostic beyond that fixed list: it doesn't know what a page
 * contains, only its name. portfolio-window.c is the only listener --
 * it connects to "page-selected" and switches its GtkStack by name. */

GtkWidget *portfolio_nav_new (void);

/* Selects the first row ("Home") and emits "page-selected" for it, so
 * the window's initial stack page and the nav's selected row agree.
 * Called once by portfolio-window.c after it has connected to
 * "page-selected" -- selecting a row during portfolio_nav_new() itself
 * would fire before any listener is connected. */
void portfolio_nav_select_home (PortfolioNav *self);

G_END_DECLS
