TEMPLATE = subdirs
SUBDIRS = nmlib nmgui test_nmlib test_nmgui
nmgui.depends = nmlib
test_nmlib.depends = nmlib
test_nmgui.depends = nmgui
