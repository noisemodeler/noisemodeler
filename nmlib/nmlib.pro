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
    codegeneration/bodygenerator.cpp \
    codegeneration/compositemodulegenerator.cpp \
    codegeneration/defaultsgenerator.cpp \
    codegeneration/functioncallbodygenerator.cpp \
    codegeneration/glsl/glslgenerator.cpp \
    codegeneration/idgenerator.cpp \
    codegeneration/inlinegenerator.cpp \
    codegeneration/modulegenerator.cpp \
    codegeneration/simplebodygenerator.cpp \
    codegeneration/unlinkedvaluedefaultsgenerator.cpp \
    codegeneration/zerodefaultsgenerator.cpp \
    model/graph.cpp \
    model/inputlink.cpp \
    model/module.cpp \
    model/moduleinput.cpp \
    model/moduleoutput.cpp \
    model/moduletype.cpp \
    model/outputlink.cpp \
    model/primitivemoduletype.cpp \
    model/signaltype.cpp \
    model/signalvalue.cpp \
    model/typemanager.cpp \
    serialization/parser.cpp \
    util/noncopyable.cpp \
    util/userdataprovider.cpp
HEADERS = \
    codegeneration/bodygenerator.hpp \
    codegeneration/compositemodulegenerator.hpp \
    codegeneration/concretemodulegenerator.hpp \
    codegeneration/defaultsgenerator.hpp \
    codegeneration/functioncallbodygenerator.hpp \
    codegeneration/glsl/glslgenerator.hpp \
    codegeneration/glsl/glslsourcefbm.hpp \
    codegeneration/glsl/glslsourcehybridmultifractal.hpp \
    codegeneration/glsl/glslsourcenoise2d.hpp \
    codegeneration/glsl/glslsourceridgedmultifractal.hpp \
    codegeneration/idgenerator.hpp \
    codegeneration/inlinegenerator.hpp \
    codegeneration/modulegenerator.hpp \
    codegeneration/simplebodygenerator.hpp \
    codegeneration/unlinkedvaluedefaultsgenerator.hpp \
    codegeneration/zerodefaultsgenerator.hpp \
    model.hpp \
    model/graph.hpp \
    model/inputlink.hpp \
    model/module.hpp \
    model/moduleinput.hpp \
    model/moduleoutput.hpp \
    model/moduletype.hpp \
    model/outputlink.hpp \
    model/primitivemoduletype.hpp \
    model/signaltype.hpp \
    model/signalvalue.hpp \
    model/typemanager.hpp \
    serialization.hpp \
    serialization/parser.hpp \
    util.hpp \
    util/makeunique.hpp \
    util/noncopyable.hpp \
    util/signals.hpp \
    util/userdataprovider.hpp
