#include "gooroom-feedback-client-window.h"

struct _GooroomFeedbackAppWindow {
  GtkApplicationWindow parent;
};

typedef struct _GooroomFeedbackAppWindowPrivate GooroomFeedbackAppWindowPrivate;

struct _GooroomFeedbackAppWindowPrivate
{
  GtkWidget *gfb_button_new_dialog;
  GtkWidget *gfb_history_scrolled_window;
  GtkWidget *gfb_history_label;
  GtkWidget *gfb_history_view;
  gchar *gfb_history;
};

G_DEFINE_TYPE_WITH_PRIVATE (GooroomFeedbackAppWindow, gooroom_feedback_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
gfb_dialog_new_button_clicked (GtkButton *widget,
                               gpointer   user_data)
{
  GooroomFeedbackDialog *dialog = gooroom_feedback_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (dialog),
                        _("Gooroom Feedback Writer"));
  gtk_dialog_run (GTK_DIALOG (dialog));
}

static gboolean
gfb_update_history (GooroomFeedbackAppWindow *win)
{
  GooroomFeedbackAppWindowPrivate *priv = NULL;

  priv = gooroom_feedback_app_window_get_instance_private (win);

  gtk_widget_destroy (priv->gfb_history_view);
  priv->gfb_history_view = gtk_viewport_new (NULL, NULL);
  gooroom_feedback_history_view_init (priv->gfb_history_view, priv->gfb_history);
  gtk_container_add (GTK_CONTAINER (priv->gfb_history_scrolled_window), priv->gfb_history_view);

  return TRUE;
}

static void
gooroom_feedback_app_window_init (GooroomFeedbackAppWindow *win)
{
  GooroomFeedbackAppWindowPrivate *priv = NULL;
  GKeyFile *key_file = g_key_file_new ();
  GtkCssProvider *css_provider = gtk_css_provider_new ();
  GtkWidget *gfb_button_new_dialog_label = gtk_label_new (_("+ New"));
  uid_t uid;
  struct passwd *pw;

  priv = gooroom_feedback_app_window_get_instance_private (win);
  gtk_widget_init_template (GTK_WIDGET (win));

  uid = geteuid ();
  pw = getpwuid (uid);

  if (pw == NULL) {
    fprintf (stderr, "getpwuid() Failed.\n");
    exit (EXIT_FAILURE);
  }

  priv->gfb_history = g_strconcat (pw->pw_dir, GOOROOM_FEEDBACK_LOG, NULL);

  gtk_css_provider_load_from_resource (css_provider, GOOROOM_FEEDBACK_CSS);
  gtk_style_context_add_provider_for_screen (gdk_screen_get_default(),
                                             GTK_STYLE_PROVIDER (css_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_widget_set_name (gfb_button_new_dialog_label, "gfb-button-new-dialog-label");
  gtk_container_add (GTK_CONTAINER (priv->gfb_button_new_dialog),
                     gfb_button_new_dialog_label);
  gtk_widget_show (gfb_button_new_dialog_label);
  priv->gfb_history_view = gtk_viewport_new (NULL, NULL);
  gooroom_feedback_history_view_init (priv->gfb_history_view, priv->gfb_history);
  gtk_container_add (GTK_CONTAINER (priv->gfb_history_scrolled_window), priv->gfb_history_view);

  g_signal_connect (priv->gfb_button_new_dialog,
                    "clicked",
                    G_CALLBACK (gfb_dialog_new_button_clicked),
                    win);
  g_timeout_add (5000,
                 G_SOURCE_FUNC (gfb_update_history),
                 win);
}

static void
gooroom_feedback_app_window_dispose (GObject *object)
{
  G_OBJECT_CLASS (gooroom_feedback_app_window_parent_class)->dispose (object);
}

static void
gooroom_feedback_app_window_class_init (GooroomFeedbackAppWindowClass *class)
{
  G_OBJECT_CLASS (class)->dispose = gooroom_feedback_app_window_dispose;

  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               GOOROOM_FEEDBACK_WINDOW_UI);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class),
                                                GooroomFeedbackAppWindow,
                                                gfb_history_label);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class),
                                                GooroomFeedbackAppWindow,
                                                gfb_history_scrolled_window);
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class),
                                                GooroomFeedbackAppWindow,
                                                gfb_button_new_dialog);
}

GooroomFeedbackAppWindow *
gooroom_feedback_app_window_new (GooroomFeedbackApp *app)
{
  return g_object_new (GOOROOM_FEEDBACK_APP_WINDOW_TYPE,
                       "application",
                       app,
                       NULL);
}
