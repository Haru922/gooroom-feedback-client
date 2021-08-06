#ifndef _GOOROOM_FEEDBACK_CLIENT_WINDOW_H_
#define _GOOROOM_FEEDBACK_CLIENT_WINDOW_H_

#include <time.h>
#include <pwd.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <glib/gi18n.h>
#include "gooroom-feedback-client-application.h"
#include "gooroom-feedback-client-history-view.h"
#include "gooroom-feedback-client-utils.h"
#include "gooroom-feedback-client-dialog.h"

#define GOOROOM_FEEDBACK_APP_WINDOW_TYPE (gooroom_feedback_app_window_get_type ())

#define GFB_TITLE_LEN 25

#define GOOROOM_FEEDBACK_WINDOW_UI "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client.ui"
#define GOOROOM_FEEDBACK_CSS       "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client.css"
#define GFB_CONF                   "/etc/gooroom/gooroom-feedback-client/gooroom-feedback-client.conf"

G_DECLARE_FINAL_TYPE (GooroomFeedbackAppWindow, gooroom_feedback_app_window, GOOROOM_FEEDBACK, APP_WINDOW, GtkApplicationWindow)

GooroomFeedbackAppWindow *gooroom_feedback_app_window_new (GooroomFeedbackApp *app);

#endif
