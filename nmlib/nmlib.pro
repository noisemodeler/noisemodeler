INCLUDEPATH += . .. ../dependencies
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums \
    -Wctor-dtor-privacy -Wzero-as-null-pointer-constant -Wuseless-cast \
    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Weffc++ \
    -Wold-style-cast
SOURCES = \
    model/inputlink.cpp \
    model/module.cpp \
    model/moduleinput.cpp \
    model/moduleoutput.cpp \
    model/moduletype.cpp \
    model/outputlink.cpp \
    model/signaltype.cpp \
    parser.cpp \
    model/typemanager.cpp \
    model/noncopyable.cpp \
    model/compositemoduletype.cpp \
    model/inputmoduletype.cpp \
    model/builtinmoduletype.cpp
HEADERS = \
    model/module.hpp \
    model/inputlink.hpp \
    model/moduleinput.hpp \
    model/moduleoutput.hpp \
    model/moduletype.hpp \
    model/outputlink.hpp \
    model/signaltype.hpp \
    model.hpp \
    parser.hpp \
    model/typemanager.hpp \
    model/noncopyable.hpp \
    model/compositemoduletype.hpp \
    model/inputmoduletype.hpp \
    model/builtinmoduletype.hpp
