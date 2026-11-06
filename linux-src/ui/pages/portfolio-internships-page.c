#include "portfolio-internships-page.h"

struct _PortfolioInternshipsPage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioInternshipsPage, portfolio_internships_page, GTK_TYPE_BOX)

static void
portfolio_internships_page_class_init (PortfolioInternshipsPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "internships-page");
}

static void
portfolio_internships_page_init (PortfolioInternshipsPage *self)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("Internships");
  GtkWidget *empty_state = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);
  GtkWidget *empty_heading = gtk_label_new ("This page is being written");
  GtkWidget *empty_body = gtk_label_new (
      "Details for two internships are being added here. In the meantime, the "
      "Education & Skills page covers my background, or you can get in touch "
      "directly for specifics.");

  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  gtk_widget_add_css_class (section, "page-section");
  gtk_widget_set_margin_top (section, 8);

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  gtk_widget_add_css_class (empty_state, "empty-state");

  gtk_widget_add_css_class (empty_heading, "empty-state-heading");
  gtk_widget_set_halign (empty_heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (empty_state), empty_heading);

  gtk_widget_add_css_class (empty_body, "empty-state-body");
  gtk_label_set_wrap (GTK_LABEL (empty_body), TRUE);
  gtk_label_set_xalign (GTK_LABEL (empty_body), 0.0);
  gtk_widget_set_halign (empty_body, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (empty_state), empty_body);

  gtk_box_append (GTK_BOX (section), empty_state);

  gtk_box_append (GTK_BOX (self), section);
}

GtkWidget *
portfolio_internships_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_INTERNSHIPS_PAGE, NULL);
}
