#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

/* Loads resources/style.css, then applies the persisted light/dark
 * preference (defaulting to light, same as web-src). Call once at
 * startup, after the default GdkDisplay exists -- this replaces the
 * old load_stylesheet() that used to live in portfolio-application.c. */
void portfolio_theme_init (void);

/* Flips between light and dark, re-skinning every open window
 * immediately via resources/style-dark.css, and persists the choice
 * under g_get_user_config_dir()/my-portfolio/theme so it's remembered
 * next launch -- the native-app equivalent of web-src/theme.js's
 * localStorage write. */
void portfolio_theme_toggle (void);

/* TRUE if dark mode is currently active. Nav uses this to pick the
 * toggle button's icon/label on startup. */
gboolean portfolio_theme_is_dark (void);

G_END_DECLS
