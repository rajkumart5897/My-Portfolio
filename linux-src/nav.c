#include "nav.h"

struct _PortfolioNav
{
  GtkBox parent_instance;

  GtkWidget *list;
};

G_DEFINE_FINAL_TYPE (PortfolioNav, portfolio_nav, GTK_TYPE_BOX)

enum
{
  SIGNAL_PAGE_SELECTED,
  N_SIGNALS,
};

static guint signals[N_SIGNALS];

/* label mirrors the <a> text in web-src's <ul class="nav-links">;
 * page_name is the matching GtkStack child name registered in
 * portfolio-window.c. */
typedef struct
{
  const char *label;
  const char *page_name;
} PortfolioNavItem;

static const PortfolioNavItem NAV_ITEMS[] = {
  { "Home", "home" },
  { "Education & Skills", "ed-skills" },
  { "Projects", "projects" },
  { "Internships", "internships" },
  { "About", "about" },
  { "Contact", "contact" },
};

static void
on_row_selected (GtkListBox    *list,
                  GtkListBoxRow *row,
                  gpointer       user_data)
{
  PortfolioNav *self = PORTFOLIO_NAV (user_data);
  const char *page_name;

  (void) list;

  if (row == NULL)
    return;

  page_name = g_object_get_data (G_OBJECT (row), "portfolio-nav-page-name");
  g_signal_emit (self, signals[SIGNAL_PAGE_SELECTED], 0, page_name);
}

static void
portfolio_nav_class_init (PortfolioNavClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "portfolio-nav");

  signals[SIGNAL_PAGE_SELECTED] =
      g_signal_new ("page-selected",
                     G_TYPE_FROM_CLASS (klass),
                     G_SIGNAL_RUN_LAST,
                     0, NULL, NULL, NULL,
                     G_TYPE_NONE, 1, G_TYPE_STRING);
}

static void
portfolio_nav_init (PortfolioNav *self)
{
  GtkWidget *brand;
  GtkWidget *brand_mark;
  GtkWidget *brand_name;
  gsize i;

  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);
  gtk_widget_add_css_class (GTK_WIDGET (self), "portfolio-nav");
  gtk_widget_set_vexpand (GTK_WIDGET (self), TRUE);

  /* Brand header: mirrors web-src's .brand ("RK" mark + "Rajkumar"). */
  brand = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_widget_add_css_class (brand, "nav-brand");

  brand_mark = gtk_label_new ("RK");
  gtk_widget_add_css_class (brand_mark, "nav-brand-mark");
  gtk_box_append (GTK_BOX (brand), brand_mark);

  brand_name = gtk_label_new ("Rajkumar");
  gtk_widget_add_css_class (brand_name, "nav-brand-name");
  gtk_box_append (GTK_BOX (brand), brand_name);

  gtk_box_append (GTK_BOX (self), brand);

  self->list = gtk_list_box_new ();
  gtk_widget_add_css_class (self->list, "nav-list");
  gtk_list_box_set_selection_mode (GTK_LIST_BOX (self->list), GTK_SELECTION_SINGLE);
  gtk_widget_set_vexpand (self->list, TRUE);

  for (i = 0; i < G_N_ELEMENTS (NAV_ITEMS); i++)
    {
      GtkWidget *row_label = gtk_label_new (NAV_ITEMS[i].label);
      GtkWidget *row;

      gtk_widget_set_halign (row_label, GTK_ALIGN_START);
      gtk_label_set_wrap (GTK_LABEL (row_label), TRUE);
      gtk_widget_add_css_class (row_label, "nav-row-label");

      row = gtk_list_box_row_new ();
      gtk_widget_add_css_class (row, "nav-row");
      gtk_list_box_row_set_child (GTK_LIST_BOX_ROW (row), row_label);
      g_object_set_data (G_OBJECT (row), "portfolio-nav-page-name",
                          (gpointer) NAV_ITEMS[i].page_name);

      gtk_list_box_append (GTK_LIST_BOX (self->list), row);
    }

  g_signal_connect (self->list, "row-selected", G_CALLBACK (on_row_selected), self);

  gtk_box_append (GTK_BOX (self), self->list);
}

GtkWidget *
portfolio_nav_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_NAV, NULL);
}

void
portfolio_nav_select_home (PortfolioNav *self)
{
  g_return_if_fail (PORTFOLIO_IS_NAV (self));

  gtk_list_box_select_row (GTK_LIST_BOX (self->list),
                            gtk_list_box_get_row_at_index (GTK_LIST_BOX (self->list), 0));
}
