#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_STAT_STRIP (portfolio_stat_strip_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioStatStrip, portfolio_stat_strip, PORTFOLIO, STAT_STRIP, GtkBox)

/* A horizontal row of "number + label" entries, e.g. "10 / Projects".
 * Content-agnostic: callers add entries with portfolio_stat_strip_add(),
 * the widget only knows how to lay them out and style them. */

GtkWidget *portfolio_stat_strip_new (void);

void portfolio_stat_strip_add (PortfolioStatStrip *self,
                                const char          *number,
                                const char          *label);

G_END_DECLS
