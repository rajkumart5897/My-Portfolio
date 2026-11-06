#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PORTFOLIO_TYPE_ED_SKILLS_PAGE (portfolio_ed_skills_page_get_type ())
G_DECLARE_FINAL_TYPE (PortfolioEdSkillsPage, portfolio_ed_skills_page, PORTFOLIO, ED_SKILLS_PAGE, GtkBox)

/* Education & Skills: education history, then core competencies.
 * Mirrors web-src/ed_skills.html's <main>. Takes no arguments, same as
 * the home page -- content is fixed for now. */

GtkWidget *portfolio_ed_skills_page_new (void);

G_END_DECLS
