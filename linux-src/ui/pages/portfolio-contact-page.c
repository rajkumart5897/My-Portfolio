#include "portfolio-contact-page.h"

struct _PortfolioContactPage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioContactPage, portfolio_contact_page, GTK_TYPE_BOX)

typedef struct
{
  const char *icon;
  const char *label;
  const char *detail;
  const char *uri;
} ContactEntry;

/* Same placeholder GitHub/LinkedIn/email values as web-src/contacts.html
 * (that file marks them with HTML comments as placeholders to be
 * replaced with real values; see docs/customization.md). */
static const ContactEntry CONTACTS[] = {
  { "gh", "GitHub", "github.com/rajkumart5897", "https://github.com/rajkumart5897" },
  { "in", "LinkedIn", "linkedin.com/in/rajkumar-arumugam-050487292",
    "https://www.linkedin.com/in/rajkumar-arumugam-050487292" },
  { "@", "Email", "rajkumart5897@gmail.com", "mailto:rajkumart5897@gmail.com" },
};

static GtkWidget *
build_contact_row (const ContactEntry *entry)
{
  GtkWidget *link = gtk_link_button_new (entry->uri);
  GtkWidget *row = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *icon = gtk_label_new (entry->icon);
  GtkWidget *text = gtk_label_new (NULL);
  char *markup;

  gtk_widget_add_css_class (icon, "contact-row-icon");

  markup = g_markup_printf_escaped ("%s — <span alpha=\"70%%\">%s</span>",
                                     entry->label, entry->detail);
  gtk_label_set_markup (GTK_LABEL (text), markup);
  g_free (markup);

  gtk_box_append (GTK_BOX (row), icon);
  gtk_box_append (GTK_BOX (row), text);

  gtk_widget_add_css_class (link, "contact-row");
  gtk_widget_set_halign (link, GTK_ALIGN_START);
  /* GtkLinkButton is a GtkButton subclass with no set_child of its own;
   * gtk_button_set_child() is the right call here. */
  gtk_button_set_child (GTK_BUTTON (link), row);

  return link;
}

static void
portfolio_contact_page_class_init (PortfolioContactPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "contact-page");
}

static void
portfolio_contact_page_init (PortfolioContactPage *self)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("Get in touch");
  GtkWidget *body = gtk_label_new (
      "Reach out about a project, an opportunity, or just to say hi — any of these work.");
  GtkWidget *list = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gsize i;

  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  gtk_widget_add_css_class (section, "page-section");
  gtk_widget_set_margin_top (section, 8);

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  gtk_widget_add_css_class (body, "hero-body");
  gtk_label_set_wrap (GTK_LABEL (body), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body), 0.0);
  gtk_widget_set_halign (body, GTK_ALIGN_START);
  gtk_widget_set_margin_bottom (body, 12);
  gtk_box_append (GTK_BOX (section), body);

  gtk_widget_add_css_class (list, "contact-list");

  for (i = 0; i < G_N_ELEMENTS (CONTACTS); i++)
    gtk_box_append (GTK_BOX (list), build_contact_row (&CONTACTS[i]));

  gtk_box_append (GTK_BOX (section), list);

  gtk_box_append (GTK_BOX (self), section);
}

GtkWidget *
portfolio_contact_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_CONTACT_PAGE, NULL);
}
