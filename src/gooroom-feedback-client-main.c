#include <glib.h>
#include <glib/gi18n.h>
#include <locale.h>
#include "gooroom-feedback-client-application.h"

int
main (int   argc,
      char *argv[])
{
  int status;
  GooroomFeedbackApp *gooroom_feedback_app;

  setlocale (LC_ALL, "");
  bindtextdomain ("gooroom-feedback-client",
                  "/usr/share/locale");
  bind_textdomain_codeset ("gooroom-feedback-client",
                           "UTF-8");
  textdomain ("gooroom-feedback-client");

  gooroom_feedback_app = gooroom_feedback_app_new ();
  status = g_application_run (G_APPLICATION (gooroom_feedback_app),
                              argc,
                              argv);
  g_object_unref (gooroom_feedback_app);

  return status;
}
