TEMPLATE = app
TARGET = test_nmgui
#QT -= #gui core
QT += qml

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
#    -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums \
#    -Wctor-dtor-privacy -Wzero-as-null-pointer-constant \
#    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion \
    -Wold-style-cast
# -Weffc++

HEADERS +=

INCLUDEPATH = . ..

SOURCES += test_transform.cpp

# TODO fix this mess of inclusions
SOURCES += ../nmgui/rendering/transform3d.cpp
HEADERS += ../nmgui/rendering/transform3d.hpp

LIBS += -L../lib -lnmlib -lgtest -lgtest_main
PRE_TARGETDEPS += ../lib/libnmlib.a

