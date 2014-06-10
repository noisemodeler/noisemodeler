TEMPLATE = app
TARGET = nm
CONFIG += console
QT -= gui core

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums \
    -Wctor-dtor-privacy -Wzero-as-null-pointer-constant -Wuseless-cast \
    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion \
    -Wold-style-cast
# -Weffc++

SOURCES += \
    main.cpp

HEADERS +=

INCLUDEPATH = . ..

win32{
    Debug {
        LIBS += -L../nmlib/debug
        PRE_TARGETDEPS += ../nmlib/debug/libnmlib.a
    }
    Release {
        LIBS += -L../nmlib/release
        PRE_TARGETDEPS += ../nmlib/release/libnmlib.a
    }
} else {
    LIBS += -L../nmlib
    PRE_TARGETDEPS += ../nmlib/libnmlib.a
}
LIBS += -lnmlib

