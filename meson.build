project('gooroom-feedback-client', 'c')

cc = meson.get_compiler('c')

gnome = import('gnome')
i18n = import('i18n')

gtk_dep = dependency('gtk+-3.0')
glib_dep = dependency('glib-2.0')
gio_dep = dependency('gio-2.0')
curl_dep = dependency('libcurl')

gooroom_feedback_client_sources = [
  'src/gooroom-feedback-client-application.c',
  'src/gooroom-feedback-client-window.c',
  'src/gooroom-feedback-client-utils.c',
  'src/gooroom-feedback-client-history-view.c',
  'src/gooroom-feedback-client-dialog.c',
  'src/gooroom-feedback-client-main.c'
]

gooroom_feedback_client_sources += gnome.compile_resources(
  'gooroom-feedback-client-resources',
  'resources/gooroom-feedback-client.gresource.xml',
  source_dir: 'resources'
)

gooroom_feedback_client = executable(
  'gooroom-feedback-client',
  gooroom_feedback_client_sources,
  dependencies: [gtk_dep, glib_dep, gio_dep, curl_dep],
  install: true,
  install_dir: '/usr/bin'
)

po_dir = join_paths(meson.source_root(), 'po')

subdir('data')
subdir('po')
