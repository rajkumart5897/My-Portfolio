#include "portfolio-stat-strip.h"

struct _PortfolioStatStrip
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioStatStrip, portfolio_stat_strip, GTK_TYPE_BOX)

static void
portfolio_stat_strip_class_init (PortfolioStatStripClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "stat-strip");
}

static void
portfolio_stat_strip_init (PortfolioStatStrip *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_HORIZONTAL);
  gtk_widget_add_css_class (GTK_WIDGET (self), "stat-strip");
  gtk_widget_set_hexpand (GTK_WIDGET (self), TRUE);
}

GtkWidget *
portfolio_stat_strip_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_STAT_STRIP, NULL);
}

void
portfolio_stat_strip_add (PortfolioStatStrip *self,
                           const char          *number,
                           const char          *label)
{
  GtkWidget *entry;
  GtkWidget *number_label;
  GtkWidget *caption_label;

  g_return_if_fail (PORTFOLIO_IS_STAT_STRIP (self));
  g_return_if_fail (number != NULL);
  g_return_if_fail (label != NULL);

  entry = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gtk_widget_add_css_class (entry, "stat-strip-entry");
  gtk_widget_set_hexpand (entry, TRUE);

  number_label = gtk_label_new (number);
  gtk_widget_add_css_class (number_label, "stat-strip-number");
  gtk_widget_set_halign (number_label, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (entry), number_label);

  caption_label = gtk_label_new (label);
  gtk_widget_add_css_class (caption_label, "stat-strip-label");
  gtk_widget_set_halign (caption_label, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (entry), caption_label);

  gtk_box_append (GTK_BOX (self), entry);
}
