#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_WINDOW (portfolio_window_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioWindow, portfolio_window, PORTFOLIO, WINDOW, GtkApplicationWindow)

/* The composition root: the one module that knows about every page and
 * widget module and wires them together. Stage 2: a sidebar (nav.c) +
 * GtkStack, switched by the nav's "page-selected" signal. The page
 * modules themselves didn't need to change from Stage 1. */

GtkWidget *portfolio_window_new (GtkApplication *application);

G_END_DECLS
