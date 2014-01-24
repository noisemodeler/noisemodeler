#Hacky way of copying data to the build folder
copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

TEMPLATE = app
TARGET = test_nmlib
QT -= gui core

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    test_parser.cpp

HEADERS +=

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib -lgtest -lgtest_main

OTHER_FILES += \
    data/onemoduletype.json
