INCLUDEPATH += . .. ../dependencies
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++11
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
    model/noncopyable.cpp
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
    model/noncopyable.hpp
