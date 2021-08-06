#ifndef _GOOROOM_FEEDBACK_CLIENT_DIALOG_H_
#define _GOOROOM_FEEDBACK_CLIENT_DIALOG_H_

#include <time.h>
#include <pwd.h>
#include <gtk/gtk.h>
#include <gio/gio.h>
#include <glib/gi18n.h>
#include "gooroom-feedback-client-utils.h"

#define GOOROOM_FEEDBACK_DIALOG_TYPE (gooroom_feedback_dialog_get_type ())

#define GFB_TITLE_LEN 25

#define GOOROOM_FEEDBACK_DIALOG_UI "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client-dialog.ui"
#define GOOROOM_FEEDBACK_CSS       "/kr/gooroom/gooroom-feedback-client/gooroom-feedback-client.css"
#define GOOROOM_FEEDBACK_CONF      "/etc/gooroom/gooroom-feedback-client/gooroom-feedback-client.conf"
#define GOOROOM_FEEDBACK_LOG       "/.local/share/gooroom-feedback-client.log"

G_DECLARE_FINAL_TYPE (GooroomFeedbackDialog, gooroom_feedback_dialog, GOOROOM_FEEDBACK, DIALOG, GtkDialog)

GooroomFeedbackDialog *gooroom_feedback_dialog_new (void);

#endif
