TEMPLATE = app
TARGET = noisemodeler-cli
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

LIBS += -L../lib
PRE_TARGETDEPS += ../lib/libnmlib.a
LIBS += -lnmlib

# Installation path
target.path = /usr/bin
INSTALLS += target

