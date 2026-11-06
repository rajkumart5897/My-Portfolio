#include "portfolio-application.h"

#include "portfolio-window.h"

struct _PortfolioApplication
{
  GtkApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioApplication, portfolio_application, GTK_TYPE_APPLICATION)

static void
load_stylesheet (void)
{
  GtkCssProvider *provider = gtk_css_provider_new ();

  gtk_css_provider_load_from_resource (provider, "/dev/portfolio/style.css");
  gtk_style_context_add_provider_for_display (
      gdk_display_get_default (),
      GTK_STYLE_PROVIDER (provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref (provider);
}

static void
portfolio_application_activate (GApplication *app)
{
  GtkWindow *window = gtk_application_get_active_window (GTK_APPLICATION (app));

  if (window == NULL)
    {
      load_stylesheet ();
      window = GTK_WINDOW (portfolio_window_new (GTK_APPLICATION (app)));
    }

  gtk_window_present (window);
}

static void
portfolio_application_class_init (PortfolioApplicationClass *klass)
{
  G_APPLICATION_CLASS (klass)->activate = portfolio_application_activate;
}

static void
portfolio_application_init (PortfolioApplication *self)
{
  (void) self;
}

GtkApplication *
portfolio_application_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_APPLICATION,
                        "application-id", "dev.portfolio.MyPortfolio",
                        "flags", G_APPLICATION_DEFAULT_FLAGS,
                        NULL);
}
