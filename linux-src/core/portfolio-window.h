#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_WINDOW (portfolio_window_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioWindow, portfolio_window, PORTFOLIO, WINDOW, GtkApplicationWindow)

/* The composition root: the one module that knows about every page and
 * widget module and wires them together. Stage 1 hosts the home page
 * directly; Stage 2 adds a sidebar + GtkStack here without the page
 * modules needing to change. */

GtkWidget *portfolio_window_new (GtkApplication *application);

G_END_DECLS
