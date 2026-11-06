#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_FEATURE_CARD (portfolio_feature_card_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioFeatureCard, portfolio_feature_card, PORTFOLIO, FEATURE_CARD, GtkBox)

/* One "featured work" card: a title, a short description, and a link-out
 * label. Content-agnostic — the home page (or any future page) passes in
 * its own text and URL. */

GtkWidget *portfolio_feature_card_new (const char *title,
                                        const char *body,
                                        const char *link_label,
                                        const char *link_uri);

G_END_DECLS
