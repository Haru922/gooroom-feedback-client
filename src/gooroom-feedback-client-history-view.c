#include "gooroom-feedback-client-history-view.h"
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>

void
gooroom_feedback_history_view_init (GtkWidget *gfb_history_view,
                                    char      *gfb_history)
{
  GtkWidget *gfb_history_box;

  gfb_history_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 1);
  gtk_widget_show_all (gfb_history_box);

  gtk_container_add (GTK_CONTAINER (gfb_history_view),
                     gfb_history_box);
  gooroom_feedback_history_view_get_items (GTK_WIDGET (gfb_history_box), gfb_history);
  gtk_widget_show_all (GTK_WIDGET (gfb_history_view));
}

static void
gfb_history_button_clicked (GtkButton *widget, gpointer user_data)
{
  GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_CLOSE,
                                              g_strcompress ((char *) user_data),
                                              NULL);
  gtk_widget_set_name (dialog,
                       "gfb-description-dialog");
  gtk_window_set_title (GTK_WINDOW (dialog),
                        _("Feedback Description"));
  g_signal_connect_swapped (dialog, "response",
                            G_CALLBACK (gtk_widget_destroy),
                            dialog);
  gtk_dialog_run (GTK_DIALOG (dialog));
}

void
gooroom_feedback_history_view_get_items (GtkWidget *gfb_history_box,
                                         char      *gfb_history)
{
  GtkWidget *gfb_history_button;
  GtkWidget *gfb_history_info;
  GtkWidget *gfb_history_details;
  GtkWidget *gfb_history_label;
  GtkWidget *gfb_history_image;
  GtkWidget *gfb_history_init_box;
  FILE *fp;
  char history[BUFSIZ];
  struct passwd *pw;
  uid_t uid;
  gchar *segments[GFB_HISTORY_COLUMNS];
  struct json_object *json_obj = NULL;
  struct json_object *iter_obj = NULL;

  gfb_history_init_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_box_pack_start (GTK_BOX (gfb_history_init_box),
                      gtk_image_new_from_resource (GFB_RESOURCE_INIT),
                      FALSE, FALSE, 5);
  gfb_history_label = gtk_label_new (_("Feedback History"));
  gtk_widget_set_name (gfb_history_label,
                       "gfb-history-info-label");
  gtk_box_pack_start (GTK_BOX (gfb_history_init_box),
                      gfb_history_label,
                      FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (gfb_history_box),
                      gfb_history_init_box,
                      FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX (gfb_history_box),
                      gtk_separator_new (GTK_ORIENTATION_HORIZONTAL),
                      FALSE, FALSE, 5);

  if (fp = fopen (gfb_history, "r"))
  {
    while (fgets (history, BUFSIZ, fp))
    {
        json_obj = json_tokener_parse (history);

        if (!json_obj) continue;
        if (!json_object_object_get_ex (json_obj, "time", &iter_obj)) {
            json_object_put (json_obj);
            continue;
        }
        segments[GFB_HISTORY_DATE] = json_object_get_string (iter_obj);
        if (!json_object_object_get_ex (json_obj, "category", &iter_obj)) {
            json_object_put (json_obj);
            continue;
        }
        segments[GFB_HISTORY_TYPE] = json_object_get_string (iter_obj);
        if (!json_object_object_get_ex (json_obj, "title", &iter_obj)) {
            json_object_put (json_obj);
            continue;
        }
        segments[GFB_HISTORY_TITLE] = json_object_get_string (iter_obj);
        if (!json_object_object_get_ex (json_obj, "description", &iter_obj)) {
            json_object_put (json_obj);
            continue;
        }
        segments[GFB_HISTORY_DESCRIPTION] = json_object_get_string (iter_obj);
        gfb_history_button = gtk_button_new ();
        gtk_widget_set_name (gfb_history_button,
                             "gfb-history-button");
        g_signal_connect (gfb_history_button,
                          "clicked",
                          G_CALLBACK (gfb_history_button_clicked),
                          g_strdup (segments[GFB_HISTORY_DESCRIPTION]));
        gfb_history_info = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
        if (!strcmp (segments[GFB_HISTORY_TYPE], "problem"))
          gfb_history_image = gtk_image_new_from_resource (GFB_RESOURCE_PROBLEM);
        else
          gfb_history_image = gtk_image_new_from_resource (GFB_RESOURCE_SUGGESTION);
        gtk_box_pack_start (GTK_BOX (gfb_history_info),
                            gfb_history_image,
                            FALSE, FALSE, 5);
        gfb_history_details = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gfb_history_label = gtk_label_new (segments[GFB_HISTORY_TITLE]);
        gtk_widget_set_name (gfb_history_label,
                             "gfb-history-title-label");
        gtk_label_set_xalign (GTK_LABEL (gfb_history_label), 0);
        gtk_box_pack_start (GTK_BOX (gfb_history_details),
                            gfb_history_label,
                            FALSE, FALSE, 5);
        gfb_history_label = gtk_label_new (segments[GFB_HISTORY_DATE]);
        gtk_widget_set_name (gfb_history_label,
                            "gfb-history-date-label");
        gtk_label_set_xalign (GTK_LABEL (gfb_history_label), 0);
        gtk_box_pack_start (GTK_BOX (gfb_history_details),
                            gfb_history_label, FALSE, FALSE, 5);
        gtk_box_pack_start (GTK_BOX (gfb_history_info),
                            gfb_history_details,
                            FALSE, FALSE, 5);
        gtk_container_add (GTK_CONTAINER (gfb_history_button),
                           gfb_history_info);
        gtk_box_pack_start (GTK_BOX (gfb_history_box),
                            gfb_history_button,
                            FALSE, FALSE, 0);
        json_object_put (json_obj);
        json_object_put (iter_obj);
    }
    fclose (fp);
  }
}
