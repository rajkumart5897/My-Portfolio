#include "portfolio-projects-page.h"

#include "../widgets/portfolio-feature-card.h"

struct _PortfolioProjectsPage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioProjectsPage, portfolio_projects_page, GTK_TYPE_BOX)

typedef struct
{
  const char *title;
  const char *body;
  const char *link_label;
  const char *link_uri;
} ProjectEntry;

/* Mirrors web-src/projects.html's .feature-grid, in the same order. The
 * writeup-only "Read the full writeup →" link there goes to
 * hardware-compat.html, which the GTK app has no local equivalent of
 * yet, so it points at the repo instead, same as the home page's
 * Hardware-Compat card. */
static const ProjectEntry PROJECTS[] = {
  { "Hardware-Compat",
    "A Linux hardware compatibility checker and driver advisor — scans PCI/USB devices, "
    "SMART disk health, battery condition and BIOS info, then recommends exact commands "
    "to fix what it finds. Built entirely on the Python standard library.",
    "View on GitHub →", "https://github.com/rajkumart5897/My-Portfolio" },
  { "ScamDetect",
    "A full-stack ML system that detects fraudulent job postings in real time using a "
    "5-model ensemble classifier plus a rule-based fraud engine, with zero external API "
    "dependencies.",
    "View on GitHub →", "https://github.com/rajkumart5897/Scam-Detector" },
  { "Personal Task Tracker",
    "A small, self-hosted, multi-user task tracker with a Flask backend, SQLite storage "
    "and a vanilla-JS frontend — no build step, no ORM, built with real attention to "
    "backend security (salted password hashes, per-user data isolation, CSRF protection).",
    "View on GitHub →", "https://github.com/rajkumart5897/Personal-Task-Tracker" },
  { "Document Verifier",
    "A blockchain-based document verification system — an admin panel uploads documents "
    "onto a simple blockchain, and anyone can publicly verify a document against it.",
    "View on GitHub →", "https://github.com/rajkumart5897/Document-Verifier" },
  { "Smart Curriculum Activity & Attendance App",
    "A full-stack MERN app for tracking curriculum activity and attendance, with an "
    "Express/MongoDB backend and a React + Tailwind frontend.",
    "View on GitHub →", "https://github.com/rajkumart5897/Smart-Curriculum-Activity-Attendance-App" },
  { "Swap-Stack",
    "A three-tier swap hierarchy (zram → fast-drive swapfile → root swapfile) built from "
    "systemd services and shell scripts, turning an 8GB Linux dev machine into a stable "
    "environment for heavy builds without OOM kills.",
    "View on GitHub →", "https://github.com/rajkumart5897/Swap-stack-with-Notification" },
  { "Nag Engine",
    "A recurring reminder app for Android that keeps nagging until a task is marked done, "
    "with fixed, escalating and snooze-loop reminder modes, quiet hours, and fully offline "
    "local storage.",
    "View on GitHub →", "https://github.com/rajkumart5897/nag-engine" },
  { "My First Linux App",
    "A beginner project building a native Linux desktop app in C with GTK, with every "
    "step — compiler, Makefile, windowing — explained from the ground up in its own docs.",
    "View on GitHub →", "https://github.com/rajkumart5897/my-linux-app" },
  { "Tribit Bluetooth Experiments",
    "Small Python scripts for discovering, connecting to, and logging notifications from "
    "a Tribit Bluetooth speaker using the Bleak BLE library.",
    "View on GitHub →", "https://github.com/rajkumart5897/tribit" },
  { "Python Developer Reference",
    "A modular, fast-navigation Python lookup system built for looking things up while "
    "coding — functions, methods, stdlib modules, and \"I want to build X\" use cases, "
    "cross-referenced and indexed.",
    "View on GitHub →", "https://github.com/rajkumart5897/program-docs" },
  { "Java & JDK 8 Practice (Forked for study.)",
    "Worked examples and practice code covering core Java (comparators, threads, file "
    "handling, collections) and JDK 8 features like lambdas, streams, and the Optional "
    "class. Prepared by Manojhd28.",
    "View on GitHub →", "https://github.com/Manojhd28/jdk8-java" },
};

static GtkWidget *
build_intro (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 4);
  GtkWidget *eyebrow = gtk_label_new ("Projects");
  GtkWidget *heading = gtk_label_new ("Things I've built");
  GtkWidget *body = gtk_label_new (
      "A mix of systems tooling, ML, and full-stack work, pulled straight from my GitHub. "
      "Hardware-Compat has the most complete writeup — the others are summarized below "
      "with links to their own READMEs.");

  gtk_widget_add_css_class (section, "page-section");
  gtk_widget_set_margin_top (section, 8);

  gtk_widget_add_css_class (eyebrow, "hero-eyebrow");
  gtk_widget_set_halign (eyebrow, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), eyebrow);

  gtk_widget_add_css_class (heading, "section-heading");
  gtk_widget_set_halign (heading, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading);

  gtk_widget_add_css_class (body, "hero-body");
  gtk_label_set_wrap (GTK_LABEL (body), TRUE);
  gtk_label_set_xalign (GTK_LABEL (body), 0.0);
  gtk_widget_set_halign (body, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), body);

  return section;
}

static GtkWidget *
build_project_list (void)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 16);
  gsize i;

  gtk_widget_add_css_class (section, "page-section");

  for (i = 0; i < G_N_ELEMENTS (PROJECTS); i++)
    {
      GtkWidget *card = portfolio_feature_card_new (PROJECTS[i].title,
                                                      PROJECTS[i].body,
                                                      PROJECTS[i].link_label,
                                                      PROJECTS[i].link_uri);

      gtk_box_append (GTK_BOX (section), card);
    }

  return section;
}

static void
portfolio_projects_page_class_init (PortfolioProjectsPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "projects-page");
}

static void
portfolio_projects_page_init (PortfolioProjectsPage *self)
{
  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  gtk_box_append (GTK_BOX (self), build_intro ());
  gtk_box_append (GTK_BOX (self), build_project_list ());
}

GtkWidget *
portfolio_projects_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_PROJECTS_PAGE, NULL);
}
