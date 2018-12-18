#Hacky way of copying data to the build folder
copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

TEMPLATE = app
TARGET = test_nmlib
QT -= gui core

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wshadow -Wwrite-strings -fshort-enums \
    -Wctor-dtor-privacy -Wzero-as-null-pointer-constant \
    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion \
    -Wold-style-cast
# -Weffc++

SOURCES += \
    test_parser.cpp \
    test_model.cpp \
    test_model_moduletype.cpp \
    test_model_constants.cpp \
    test_serializer.cpp \
    test_codegeneration_glsl.cpp \
    readfile.cpp

HEADERS += \
    readfile.hpp

INCLUDEPATH = . ..

LIBS += -L../lib -lnmlib -lgtest -lgtest_main
PRE_TARGETDEPS += ../lib/libnmlib.a

OTHER_FILES += \
    data/constants.nm.json \
    data/onemoduletype.nm.json \
    data/complextest.json \
    data/multipletypes.nm.json
