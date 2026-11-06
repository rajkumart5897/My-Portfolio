#include "portfolio-window.h"

#include "../ui/pages/portfolio-home-page.h"

struct _PortfolioWindow
{
  GtkApplicationWindow parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioWindow, portfolio_window, GTK_TYPE_APPLICATION_WINDOW)

static void
portfolio_window_class_init (PortfolioWindowClass *klass)
{
  (void) klass;
}

static void
portfolio_window_init (PortfolioWindow *self)
{
  GtkWidget *scroller;
  GtkWidget *home_page;

  gtk_widget_add_css_class (GTK_WIDGET (self), "portfolio-window");
  gtk_window_set_title (GTK_WINDOW (self), "Rajkumar — Portfolio");
  gtk_window_set_default_size (GTK_WINDOW (self), 960, 720);

  scroller = gtk_scrolled_window_new ();
  gtk_widget_add_css_class (scroller, "portfolio-scroller");
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroller),
                                   GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  /* Stage 1: the window hosts the home page directly. Stage 2 swaps this
   * for a sidebar + GtkStack that home_page becomes one page of. */
  home_page = portfolio_home_page_new ();
  gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scroller), home_page);

  gtk_window_set_child (GTK_WINDOW (self), scroller);
}

GtkWidget *
portfolio_window_new (GtkApplication *application)
{
  g_return_val_if_fail (GTK_IS_APPLICATION (application), NULL);

  return g_object_new (PORTFOLIO_TYPE_WINDOW,
                        "application", application,
                        NULL);
}
