#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_CONTACT_PAGE (portfolio_contact_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioContactPage, portfolio_contact_page, PORTFOLIO, CONTACT_PAGE, GtkBox)

/* Contact: GitHub, LinkedIn and email links. Mirrors
 * web-src/contacts.html's <main>. Takes no arguments; see
 * docs/customization.md if the LinkedIn/email placeholders here ever
 * need to change -- they're the same ones used on the HTML site. */

GtkWidget *portfolio_contact_page_new (void);

G_END_DECLS
