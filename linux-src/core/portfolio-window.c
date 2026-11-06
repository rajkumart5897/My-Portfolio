#include "portfolio-window.h"

#include "../nav.h"
#include "../ui/pages/portfolio-home-page.h"
#include "../ui/pages/portfolio-ed-skills-page.h"
#include "../ui/pages/portfolio-projects-page.h"
#include "../ui/pages/portfolio-internships-page.h"
#include "../ui/pages/portfolio-about-page.h"
#include "../ui/pages/portfolio-contact-page.h"

struct _PortfolioWindow
{
  GtkApplicationWindow parent_instance;

  GtkWidget *stack;
};

G_DEFINE_FINAL_TYPE (PortfolioWindow, portfolio_window, GTK_TYPE_APPLICATION_WINDOW)

static void
portfolio_window_class_init (PortfolioWindowClass *klass)
{
  (void) klass;
}

static void
on_nav_page_selected (PortfolioNav *nav,
                       const char   *page_name,
                       gpointer      user_data)
{
  PortfolioWindow *self = PORTFOLIO_WINDOW (user_data);

  (void) nav;

  if (page_name != NULL)
    gtk_stack_set_visible_child_name (GTK_STACK (self->stack), page_name);
}

/* Wraps a page in its own scroller so the sidebar nav stays fixed in
 * place while a page's own content scrolls -- matches web-src, where
 * <nav class="site-nav"> is a sibling of <main>, not inside it. */
static GtkWidget *
wrap_in_scroller (GtkWidget *page)
{
  GtkWidget *scroller = gtk_scrolled_window_new ();

  gtk_widget_add_css_class (scroller, "portfolio-scroller");
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroller),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scroller), page);

  return scroller;
}

static void
portfolio_window_init (PortfolioWindow *self)
{
  GtkWidget *root;
  GtkWidget *nav;
  GtkWidget *separator;

  gtk_widget_add_css_class (GTK_WIDGET (self), "portfolio-window");
  gtk_window_set_title (GTK_WINDOW (self), "Rajkumar — Portfolio");
  gtk_window_set_default_size (GTK_WINDOW (self), 1040, 720);

  root = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

  /* Stage 2: sidebar + GtkStack, built from nav.c's fixed page list --
   * mirrors web-src's <nav class="site-nav"> links 1:1 (same six
   * labels, same order, same destinations). */
  nav = portfolio_nav_new ();
  gtk_box_append (GTK_BOX (root), nav);

  separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  gtk_widget_add_css_class (separator, "nav-separator");
  gtk_box_append (GTK_BOX (root), separator);

  self->stack = gtk_stack_new ();
  gtk_stack_set_transition_type (GTK_STACK (self->stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
  gtk_widget_set_hexpand (self->stack, TRUE);

  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_home_page_new ()), "home");
  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_ed_skills_page_new ()), "ed-skills");
  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_projects_page_new ()), "projects");
  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_internships_page_new ()), "internships");
  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_about_page_new ()), "about");
  gtk_stack_add_named (GTK_STACK (self->stack),
                        wrap_in_scroller (portfolio_contact_page_new ()), "contact");

  gtk_box_append (GTK_BOX (root), self->stack);

  g_signal_connect (nav, "page-selected", G_CALLBACK (on_nav_page_selected), self);

  /* Fires the first "page-selected" now that the signal above is
   * connected, so the stack's initial page and the nav's selected row
   * agree without a separate gtk_stack_set_visible_child_name() call. */
  portfolio_nav_select_home (PORTFOLIO_NAV (nav));

  gtk_window_set_child (GTK_WINDOW (self), root);
}

GtkWidget *
portfolio_window_new (GtkApplication *application)
{
  g_return_val_if_fail (GTK_IS_APPLICATION (application), NULL);

  return g_object_new (PORTFOLIO_TYPE_WINDOW,
                        "application", application,
                        NULL);
}
