TEMPLATE = subdirs
SUBDIRS = nmlib nmgui
nmgui.depends = nmlib

#run qmake with CONFIG+=build_tests to build the tests
build_tests {
    SUBDIRS += test_nmlib test_nmgui
    test_nmlib.depends = nmlib
    test_nmgui.depends = nmgui
}
