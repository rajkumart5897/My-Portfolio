#include "portfolio-ed-skills-page.h"

struct _PortfolioEdSkillsPage
{
  GtkBox parent_instance;
};

G_DEFINE_FINAL_TYPE (PortfolioEdSkillsPage, portfolio_ed_skills_page, GTK_TYPE_BOX)

typedef struct
{
  const char *col1;
  const char *col2;
  const char *items[4];
} TableRow;

static const TableRow EDUCATION_ROWS[] = {
  { "B.E. Computer Science Engineering", "Velammal Engineering College, Surapet",
    { "Expected graduation: 2027", NULL } },
  { "Higher Secondary (12th) & SSLC", "Sir Ramaswamy Mudaliar Higher Secondary School, Chennai",
    { "2016 – 2023", NULL } },
  { "Nursery & Primary Education", "St. Joseph Nursery and Primary School, Ambattur, Chennai",
    { "2010 – 2016", NULL } },
};

static const TableRow COMPETENCY_ROWS[] = {
  { "Programming languages", "Core & applied coding",
    { "Java, C, and C++ (foundational)",
      "Python (AI, data science, scripting)",
      "JavaScript & TypeScript (web development)", NULL } },
  { "Foundational CS", "Theory & logic",
    { "Data structures & algorithms (DSA)",
      "Object-oriented programming (OOP)",
      "Database management systems (SQL, NoSQL)", NULL } },
  { "System architecture", "Backend & infrastructure",
    { "Operating systems & computer networks",
      "RESTful APIs and microservices",
      "Git, GitHub, and version control", NULL } },
  { "Modern tech stack", "Specialized development",
    { "Frontend: HTML, CSS, React.js, Vue.js",
      "Cloud: AWS, Azure, Google Cloud",
      "DevOps: Docker, Kubernetes, CI/CD pipelines", NULL } },
  { "Professional skills", "Soft skills & problem solving",
    { "System design and architecture",
      "Agile methodologies & team collaboration",
      "Analytical thinking and debugging", NULL } },
};

static GtkWidget *
build_items_column (const char * const *items)
{
  GtkWidget *col = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
  gsize i;

  for (i = 0; items[i] != NULL; i++)
    {
      char *bulleted = g_strdup_printf ("• %s", items[i]);
      GtkWidget *label = gtk_label_new (bulleted);

      gtk_widget_add_css_class (label, "skills-table-item");
      gtk_label_set_wrap (GTK_LABEL (label), TRUE);
      gtk_label_set_xalign (GTK_LABEL (label), 0.0);
      gtk_widget_set_halign (label, GTK_ALIGN_START);
      gtk_box_append (GTK_BOX (col), label);

      g_free (bulleted);
    }

  return col;
}

static GtkWidget *
build_table (const char *col1_heading,
             const char *col2_heading,
             const char *col3_heading,
             const TableRow *rows,
             gsize n_rows)
{
  GtkWidget *grid = gtk_grid_new ();
  gsize i;

  gtk_widget_add_css_class (grid, "skills-table");
  gtk_grid_set_row_spacing (GTK_GRID (grid), 10);
  gtk_grid_set_column_spacing (GTK_GRID (grid), 24);
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), FALSE);

  {
    GtkWidget *h1 = gtk_label_new (col1_heading);
    GtkWidget *h2 = gtk_label_new (col2_heading);
    GtkWidget *h3 = gtk_label_new (col3_heading);

    gtk_widget_add_css_class (h1, "skills-table-heading");
    gtk_widget_add_css_class (h2, "skills-table-heading");
    gtk_widget_add_css_class (h3, "skills-table-heading");
    gtk_widget_set_halign (h1, GTK_ALIGN_START);
    gtk_widget_set_halign (h2, GTK_ALIGN_START);
    gtk_widget_set_halign (h3, GTK_ALIGN_START);

    gtk_grid_attach (GTK_GRID (grid), h1, 0, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), h2, 1, 0, 1, 1);
    gtk_grid_attach (GTK_GRID (grid), h3, 2, 0, 1, 1);
  }

  for (i = 0; i < n_rows; i++)
    {
      GtkWidget *col1 = gtk_label_new (rows[i].col1);
      GtkWidget *col2 = gtk_label_new (rows[i].col2);
      GtkWidget *col3 = build_items_column (rows[i].items);
      int grid_row = (int) i + 1;

      gtk_widget_add_css_class (col1, "skill-category");
      gtk_widget_set_halign (col1, GTK_ALIGN_START);
      gtk_label_set_wrap (GTK_LABEL (col1), TRUE);
      gtk_label_set_xalign (GTK_LABEL (col1), 0.0);
      gtk_widget_set_valign (col1, GTK_ALIGN_START);

      gtk_widget_set_halign (col2, GTK_ALIGN_START);
      gtk_label_set_wrap (GTK_LABEL (col2), TRUE);
      gtk_label_set_xalign (GTK_LABEL (col2), 0.0);
      gtk_widget_set_valign (col2, GTK_ALIGN_START);
      gtk_widget_add_css_class (col2, "skills-table-institution");

      gtk_grid_attach (GTK_GRID (grid), col1, 0, grid_row, 1, 1);
      gtk_grid_attach (GTK_GRID (grid), col2, 1, grid_row, 1, 1);
      gtk_grid_attach (GTK_GRID (grid), col3, 2, grid_row, 1, 1);
    }

  return grid;
}

static GtkWidget *
build_section (const char *heading, GtkWidget *table)
{
  GtkWidget *section = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *heading_label = gtk_label_new (heading);

  gtk_widget_add_css_class (section, "page-section");

  gtk_widget_add_css_class (heading_label, "section-heading");
  gtk_widget_set_halign (heading_label, GTK_ALIGN_START);
  gtk_box_append (GTK_BOX (section), heading_label);

  gtk_box_append (GTK_BOX (section), table);

  return section;
}

static void
portfolio_ed_skills_page_class_init (PortfolioEdSkillsPageClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_css_name (widget_class, "ed-skills-page");
}

static void
portfolio_ed_skills_page_init (PortfolioEdSkillsPage *self)
{
  GtkWidget *education_table;
  GtkWidget *competency_table;

  gtk_orientable_set_orientation (GTK_ORIENTABLE (self), GTK_ORIENTATION_VERTICAL);

  education_table = build_table ("Qualification", "Institution", "Duration / status",
                                  EDUCATION_ROWS, G_N_ELEMENTS (EDUCATION_ROWS));
  gtk_box_append (GTK_BOX (self), build_section ("Education", education_table));

  competency_table = build_table ("Category", "Domain", "Technologies & details",
                                   COMPETENCY_ROWS, G_N_ELEMENTS (COMPETENCY_ROWS));
  gtk_box_append (GTK_BOX (self), build_section ("Core competencies", competency_table));
}

GtkWidget *
portfolio_ed_skills_page_new (void)
{
  return g_object_new (PORTFOLIO_TYPE_ED_SKILLS_PAGE, NULL);
}
