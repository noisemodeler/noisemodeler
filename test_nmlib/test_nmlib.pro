TEMPLATE = app
TARGET = test_nmlib
QT -= gui core

SOURCES += main.cpp \
    test_serialization.cpp

HEADERS += \
    test_serialization.hpp

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib

