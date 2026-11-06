#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_INTERNSHIPS_PAGE (portfolio_internships_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioInternshipsPage, portfolio_internships_page, PORTFOLIO, INTERNSHIPS_PAGE, GtkBox)

/* Internships: an empty-state placeholder, same as
 * web-src/internships.html -- content for the two internships hasn't
 * been written on either build yet. Takes no arguments. */

GtkWidget *portfolio_internships_page_new (void);

G_END_DECLS
