TEMPLATE = subdirs
SUBDIRS = nmlib nmgui test_nmlib
nmgui.depends = nmlib
test_nmlib.depends = nmlib
