#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_APPLICATION (portfolio_application_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioApplication, portfolio_application, PORTFOLIO, APPLICATION, GtkApplication)

GtkApplication *portfolio_application_new (void);

G_END_DECLS
