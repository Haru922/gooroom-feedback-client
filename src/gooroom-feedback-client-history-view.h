#ifndef _GOOROOM_FEEDBACK_CLIENT_HISTORY_VIEW_H_
#define _GOOROOM_FEEDBACK_CLIENT_HISTORY_VIEW_H_

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <pwd.h>

#define GFB_RESOURCE_INIT       "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client-init.svg"
#define GFB_RESOURCE_PROBLEM    "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client-problem.svg"
#define GFB_RESOURCE_SUGGESTION "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client-suggestion.svg"

enum _gfb_history_column {
  GFB_HISTORY_DATE,
  GFB_HISTORY_TITLE,
  GFB_HISTORY_TYPE,
  GFB_HISTORY_DESCRIPTION,
  GFB_HISTORY_COLUMNS
};

void gooroom_feedback_history_view_init      (GtkWidget *gfb_history_window, char *gfb_history);
void gooroom_feedback_history_view_get_items (GtkWidget *gfb_history_view, char *gfb_history);

#endif
