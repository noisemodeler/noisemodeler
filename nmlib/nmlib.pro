INCLUDEPATH += . .. ../dependencies
TEMPLATE = lib
CONFIG = staticlib
QMAKE_CXXFLAGS += -std=c++11
SOURCES = \
    module.cpp \
    signaltype.cpp \
    moduletype.cpp \
    inputlink.cpp \
    outputlink.cpp \
    moduleinput.cpp \
    moduleoutput.cpp
HEADERS = \
    module.hpp \
    signaltype.hpp \
    moduletype.hpp \
    inputlink.hpp \
    outputlink.hpp \
    moduleinput.hpp \
    moduleoutput.hpp
