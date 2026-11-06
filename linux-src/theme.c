#include "theme.h"

#include <gio/gio.h>

static GtkCssProvider *base_provider = NULL;
static GtkCssProvider *dark_provider = NULL;
static gboolean dark_active = FALSE;

static char *
config_file_path (void)
{
  return g_build_filename (g_get_user_config_dir (), "my-portfolio", "theme", NULL);
}

static gboolean
load_persisted_dark_preference (void)
{
  char *path = config_file_path ();
  char *contents = NULL;
  gboolean is_dark = FALSE;

  if (g_file_get_contents (path, &contents, NULL, NULL))
    {
      is_dark = g_strcmp0 (g_strstrip (contents), "dark") == 0;
      g_free (contents);
    }

  g_free (path);
  return is_dark;
}

static void
persist_dark_preference (gboolean is_dark)
{
  char *path = config_file_path ();
  char *dir = g_path_get_dirname (path);

  g_mkdir_with_parents (dir, 0700);
  g_file_set_contents (path, is_dark ? "dark" : "light", -1, NULL);

  g_free (dir);
  g_free (path);
}

static void
apply_dark (gboolean is_dark)
{
  GdkDisplay *display = gdk_display_get_default ();

  /* style-dark.css re-declares the same @define-color names as
   * style.css; layering it at a higher priority is enough to re-skin
   * every rule in style.css, since none of them use literal hex
   * values -- see the comment at the top of style-dark.css. */
  if (is_dark)
    gtk_style_context_add_provider_for_display (
        display, GTK_STYLE_PROVIDER (dark_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION + 1);
  else
    gtk_style_context_remove_provider_for_display (
        display, GTK_STYLE_PROVIDER (dark_provider));

  /* Also flips the active system theme's own light/dark variant
   * (Adwaita etc.), same as docs/theming.md describes -- covers any
   * native chrome our stylesheet doesn't touch. */
  g_object_set (gtk_settings_get_default (),
                "gtk-application-prefer-dark-theme", is_dark, NULL);

  dark_active = is_dark;
}

void
portfolio_theme_init (void)
{
  base_provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_resource (base_provider, "/dev/portfolio/style.css");
  gtk_style_context_add_provider_for_display (
      gdk_display_get_default (), GTK_STYLE_PROVIDER (base_provider),
      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  dark_provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_resource (dark_provider, "/dev/portfolio/style-dark.css");

  apply_dark (load_persisted_dark_preference ());
}

void
portfolio_theme_toggle (void)
{
  apply_dark (!dark_active);
  persist_dark_preference (dark_active);
}

gboolean
portfolio_theme_is_dark (void)
{
  return dark_active;
}
