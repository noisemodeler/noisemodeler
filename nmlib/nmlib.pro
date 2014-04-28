INCLUDEPATH += . .. ../dependencies
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums \
    -Wctor-dtor-privacy -Wzero-as-null-pointer-constant -Wuseless-cast \
    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion \
    -Wold-style-cast
#flags that should probably be added again later:
#CMAKE_CXXFLAGS += -Weffc++

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
    util/userdataprovider.cpp \
    util/noncopyable.cpp \
    codegeneration/idgenerator.cpp \
    codegeneration/inlinegenerator.cpp \
    model/primitivemoduletype.cpp \
    codegeneration/defaultsgenerator.cpp \
    codegeneration/bodygenerator.cpp \
    codegeneration/modulegenerator.cpp \
    codegeneration/compositemodulegenerator.cpp \
    codegeneration/zerodefaultsgenerator.cpp \
    model/signalvalue.cpp \
    codegeneration/simplebodygenerator.cpp \
    codegeneration/functioncallbodygenerator.cpp \
    codegeneration/glsl/glslgenerator.cpp \
    model/graph.cpp \
    codegeneration/unlinkedvaluedefaultsgenerator.cpp
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
    util/userdataprovider.hpp \
    util/noncopyable.hpp \
    util/signals.hpp \
    codegeneration/idgenerator.hpp \
    codegeneration/inlinegenerator.hpp \
    model/primitivemoduletype.hpp \
    codegeneration/defaultsgenerator.hpp \
    codegeneration/bodygenerator.hpp \
    codegeneration/modulegenerator.hpp \
    codegeneration/compositemodulegenerator.hpp \
    codegeneration/zerodefaultsgenerator.hpp \
    model/signalvalue.hpp \
    codegeneration/simplebodygenerator.hpp \
    util/makeunique.hpp \
    util.hpp \
    codegeneration/functioncallbodygenerator.hpp \
    codegeneration/glsl/glslgenerator.hpp \
    model/graph.hpp \
    codegeneration/glsl/glslsourcenoise2d.hpp \
    codegeneration/glsl/glslsourcefbm.hpp \
    codegeneration/unlinkedvaluedefaultsgenerator.hpp \
    codegeneration/glsl/glslsourceridgedmultifractal.hpp
