#include "portfolio-feature-card.h"

struct _PortfolioFeatureCard
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioFeatureCard, portfolio_feature_card, GTK_TYPE_BOX)

static void
portfolio_feature_card_class_init (PortfolioFeatureCardClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "feature-card");
}

static void
portfolio_feature_card_init (PortfolioFeatureCard *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);
  gtk_box_set_spacing (GTK_BOX (self), 8);
  gtk_widget_add_css_class (GTK_WIDGET (self), "feature-card");
}

GtkWidget *
portfolio_feature_card_new (const char *title,
                             const char *body,
                             const char *link_label,
                             const char *link_uri)
{
  PortfolioFeatureCard *self;
  GtkWidget *title_label;
  GtkWidget *body_label;

  g_return_val_if_fail (title != NULL, NULL);
  g_return_val_if_fail (body != NULL, NULL);

  self = g_object_new (PORTFOLIO_TYPE_FEATURE_CARD, NULL);

  title_label = gtk_label_new (title);
  gtk_widget_add_css_class (title_label, "feature-card-title");
  gtk_widget_set_halign (title_label, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (self), title_label);

  body_label = gtk_label_new (body);
  gtk_widget_add_css_class (body_label, "feature-card-body");
  gtk_label_set_wrap (GTK_LABEL (body_label), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body_label), 0.0);
  gtk_widget_set_halign (body_label, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (self), body_label);

  if (link_label != NULL && link_uri != NULL)
    {
      GtkWidget *link = gtk_link_button_new_with_label (link_uri, link_label);

      gtk_widget_add_css_class (link, "feature-card-link");
      gtk_widget_set_halign (link, GTK_ALIGN_START);
      gtk_box_append (GTK_BOX (self), link);
    }

  return GTK_WIDGET (self);
}
