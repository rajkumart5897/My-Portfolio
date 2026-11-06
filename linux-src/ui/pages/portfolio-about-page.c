#include "portfolio-about-page.h"

struct _PortfolioAboutPage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioAboutPage, portfolio_about_page, GTK_TYPE_BOX)

static const char *const JOURNEY_ITEMS[] = {
  "Decided early on to pursue the path of B.E. Computer Science Engineering.",
  "Introduced to Python during 12th standard.",
  "Settled on a concrete domain — full-stack web development.",
  "From 2023 onward: focused on web development through college.",
};

static const char *const INTEREST_TAGS[] = {
  "Full-stack web development",
  "Android app development",
  "Backend development",
  "Frontend development",
  "Linux",
};

static GtkWidget *
build_hero (void)
{
  GtkWidget *hero = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 32);
  GtkWidget *text_col = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  GtkWidget *eyebrow = gtk_label_new ("About");
  GtkWidget *heading = gtk_label_new (
      "Implementing solutions to real-world problems through web technology.");
  GtkWidget *body1 = gtk_label_new (
      "I'm a computer science student with a strong interest in technology and software "
      "development, backed by a solid educational foundation and hands-on experience "
      "from projects and internships.");
  GtkWidget *body2 = gtk_label_new (
      "In my free time I explore new technologies, learn programming languages, and "
      "contribute to open-source projects — always looking for the next challenge in an "
      "ever-evolving field.");
  GtkWidget *portrait_frame;
  GtkWidget *portrait;

  gtk_widget_add_css_class (hero, "hero");

  gtk_widget_add_css_class (eyebrow, "hero-eyebrow");
  gtk_widget_set_halign (eyebrow, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (text_col), eyebrow);

  gtk_widget_add_css_class (heading, "about-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_label_set_wrap (GTK_LABEL (heading), TRUE);
  gtk_label_set_xalign (GTK_LABEL (heading), 0.0);
  gtk_box_append (GTK_BOX (text_col), heading);

  gtk_widget_add_css_class (body1, "hero-body");
  gtk_label_set_wrap (GTK_LABEL (body1), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body1), 0.0);
  gtk_widget_set_halign (body1, GTK_ALIGN_START);
  gtk_widget_set_margin_top (body1, 8);
  gtk_box_append (GTK_BOX (text_col), body1);

  gtk_widget_add_css_class (body2, "hero-body");
  gtk_label_set_wrap (GTK_LABEL (body2), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body2), 0.0);
  gtk_widget_set_halign (body2, GTK_ALIGN_START);
  gtk_widget_set_margin_top (body2, 8);
  gtk_box_append (GTK_BOX (text_col), body2);

  gtk_widget_set_hexpand (text_col, TRUE);
  gtk_box_append (GTK_BOX (hero), text_col);

  portrait_frame = gtk_frame_new (NULL);
  gtk_widget_add_css_class (portrait_frame, "hero-portrait");
  gtk_widget_set_valign (portrait_frame, GTK_ALIGN_CENTER);

  portrait = gtk_picture_new_for_resource ("/dev/portfolio/portrait.jpg");
  gtk_picture_set_content_fit (GTK_PICTURE (portrait), GTK_CONTENT_FIT_COVER);
  gtk_widget_set_size_request (portrait, 220, 280);
  gtk_frame_set_child (GTK_FRAME (portrait_frame), portrait);

  gtk_box_append (GTK_BOX (hero), portrait_frame);

  return hero;
}

static GtkWidget *
build_journey_section (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("Journey");
  GtkWidget *list = gtk_box_new (GTK_ORIENTATION_VERTICAL, 8);
  gsize i;

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  for (i = 0; i < G_N_ELEMENTS (JOURNEY_ITEMS); i++)
    {
      char *bulleted = g_strdup_printf ("• %s", JOURNEY_ITEMS[i]);
      GtkWidget *label = gtk_label_new (bulleted);

      gtk_widget_add_css_class (label, "timeline-item");
      gtk_label_set_wrap (GTK_LABEL (label), TRUE);
      gtk_label_set_xalign (GTK_LABEL (label), 0.0);
      gtk_widget_set_halign (label, GTK_ALIGN_START);
      gtk_box_append (GTK_BOX (list), label);

      g_free (bulleted);
    }

  gtk_box_append (GTK_BOX (section), list);

  return section;
}

static GtkWidget *
build_interests_section (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("Interests");
  GtkWidget *tag_row = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gsize i;

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  gtk_widget_add_css_class (tag_row, "tag-row");
  gtk_widget_set_halign (tag_row, GTK_ALIGN_START);

  for (i = 0; i < G_N_ELEMENTS (INTEREST_TAGS); i++)
    {
      GtkWidget *tag = gtk_label_new (INTEREST_TAGS[i]);

      gtk_widget_add_css_class (tag, "tag-pill");
      gtk_box_append (GTK_BOX (tag_row), tag);
    }

  gtk_box_append (GTK_BOX (section), tag_row);

  return section;
}

static void
portfolio_about_page_class_init (PortfolioAboutPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "about-page");
}

static void
portfolio_about_page_init (PortfolioAboutPage *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  gtk_box_append (GTK_BOX (self), build_hero ());
  gtk_box_append (GTK_BOX (self), build_journey_section ());
  gtk_box_append (GTK_BOX (self), build_interests_section ());
}

GtkWidget *
portfolio_about_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_ABOUT_PAGE, NULL);
}
