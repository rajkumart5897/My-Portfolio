#include "portfolio-home-page.h"

#include "../widgets/portfolio-stat-strip.h"
#include "../widgets/portfolio-feature-card.h"

struct _PortfolioHomePage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioHomePage, portfolio_home_page, GTK_TYPE_BOX)

static GtkWidget *
build_hero (void)
{
  GtkWidget *hero = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 32);
  GtkWidget *text_col = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  GtkWidget *eyebrow;
  GtkWidget *heading;
  GtkWidget *role;
  GtkWidget *body;
  GtkWidget *buttons;
  GtkWidget *view_projects_btn;
  GtkWidget *resume_btn;
  GtkWidget *portrait_frame;
  GtkWidget *portrait;

  gtk_widget_add_css_class (hero, "hero");

  eyebrow = gtk_label_new ("B.E. Computer Science Engineering · Full-Stack Developer");
  gtk_widget_add_css_class (eyebrow, "hero-eyebrow");
  gtk_widget_set_halign (eyebrow, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (text_col), eyebrow);

  heading = gtk_label_new ("Hi, I'm Rajkumar.");
  gtk_widget_add_css_class (heading, "hero-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (text_col), heading);

  role = gtk_label_new ("I build practical software and enjoy solving real-world problems with code.");
  gtk_widget_add_css_class (role, "hero-role");
  gtk_widget_set_halign (role, GTK_ALIGN_START);
  gtk_label_set_wrap (GTK_LABEL (role), TRUE);
  gtk_box_append (GTK_BOX (text_col), role);

  body = gtk_label_new ("I'm a computer science student focused on full-stack web development, "
                         "with a growing interest in backend systems and cloud computing. I like "
                         "picking things apart to understand how they work — Linux internals, "
                         "networking, and the tools developers use every day.");
  gtk_widget_add_css_class (body, "hero-body");
  gtk_label_set_wrap (GTK_LABEL (body), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body), 0.0);
  gtk_widget_set_halign (body, GTK_ALIGN_START);
  gtk_widget_set_margin_top (body, 8);
  gtk_box_append (GTK_BOX (text_col), body);

  buttons = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
  gtk_widget_set_margin_top (buttons, 16);

  view_projects_btn = gtk_button_new_with_label ("View projects");
  gtk_widget_add_css_class (view_projects_btn, "btn");
  gtk_widget_add_css_class (view_projects_btn, "suggested");
  gtk_box_append (GTK_BOX (buttons), view_projects_btn);

  resume_btn = gtk_button_new_with_label ("📄 Download resume");
  gtk_widget_add_css_class (resume_btn, "btn");
  gtk_widget_add_css_class (resume_btn, "ghost");
  gtk_box_append (GTK_BOX (buttons), resume_btn);

  gtk_box_append (GTK_BOX (text_col), buttons);

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
build_at_a_glance_section (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("At a glance");
  GtkWidget *strip = portfolio_stat_strip_new ();

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  portfolio_stat_strip_add (PORTFOLIO_STAT_STRIP (strip), "10", "Projects");
  portfolio_stat_strip_add (PORTFOLIO_STAT_STRIP (strip), "2", "Internships");
  portfolio_stat_strip_add (PORTFOLIO_STAT_STRIP (strip), "10+", "Technologies");
  portfolio_stat_strip_add (PORTFOLIO_STAT_STRIP (strip), "2027", "Expected graduation");
  gtk_box_append (GTK_BOX (section), strip);

  return section;
}

static GtkWidget *
build_featured_work_section (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("Featured work");
  GtkWidget *grid = gtk_grid_new ();
  GtkWidget *hardware_compat;
  GtkWidget *scam_detect;
  GtkWidget *task_tracker;

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  gtk_widget_add_css_class (grid, "feature-grid");
  gtk_grid_set_row_spacing (GTK_GRID (grid), 16);
  gtk_grid_set_column_spacing (GTK_GRID (grid), 16);
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);

  hardware_compat = portfolio_feature_card_new (
      "Hardware-Compat",
      "A Linux hardware compatibility checker that scans PCI/USB devices, driver "
      "status, SMART disk health and battery condition, then recommends exact "
      "fix commands — no third-party Python packages required.",
      "Read the writeup →", "https://github.com/rajkumart5897/My-Portfolio");
  gtk_widget_set_vexpand (hardware_compat, TRUE);
  gtk_grid_attach (GTK_GRID (grid), hardware_compat, 0, 0, 1, 2);

  scam_detect = portfolio_feature_card_new (
      "ScamDetect",
      "A full-stack ML system that detects fraudulent job postings in real time "
      "with a 5-model ensemble classifier and a rule-based fraud engine.",
      "View on GitHub →", "https://github.com/rajkumart5897/Scam-Detector");
  gtk_grid_attach (GTK_GRID (grid), scam_detect, 1, 0, 1, 1);

  task_tracker = portfolio_feature_card_new (
      "Personal Task Tracker",
      "A self-hosted, multi-user task tracker with a Flask + SQLite backend and "
      "a vanilla-JS frontend, built with real attention to backend security.",
      "View on GitHub →", "https://github.com/rajkumart5897/Personal-Task-Tracker");
  gtk_grid_attach (GTK_GRID (grid), task_tracker, 1, 1, 1, 1);

  gtk_box_append (GTK_BOX (section), grid);

  return section;
}

static GtkWidget *
build_about_teaser_section (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading = gtk_label_new ("About");
  GtkWidget *teaser;

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  teaser = gtk_label_new ("I'm a computer science student interested in backend development "
                           "and cloud computing. I enjoy building practical software while "
                           "continuously learning Linux, networking, and modern web "
                           "technologies. More about me → (the About page lands in Stage 3.)");
  gtk_widget_add_css_class (teaser, "about-teaser");
  gtk_label_set_wrap (GTK_LABEL (teaser), TRUE);
  gtk_label_set_xalign (GTK_LABEL (teaser), 0.0);
  gtk_widget_set_halign (teaser, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), teaser);

  return section;
}

static void
portfolio_home_page_class_init (PortfolioHomePageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "home-page");
}

static void
portfolio_home_page_init (PortfolioHomePage *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  gtk_box_append (GTK_BOX (self), build_hero ());
  gtk_box_append (GTK_BOX (self), build_at_a_glance_section ());
  gtk_box_append (GTK_BOX (self), build_featured_work_section ());
  gtk_box_append (GTK_BOX (self), build_about_teaser_section ());
}

GtkWidget *
portfolio_home_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_HOME_PAGE, NULL);
}
