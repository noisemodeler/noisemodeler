# Add more folders to ship with the application, here
#folder_01.source = qml/noisemodeler
#folder_01.target = qml
#DEPLOYMENTFOLDERS = folder_01

TEMPLATE = app

TARGET = nmgui
QT += core gui qml quick svg widgets
CONFIG += static
QTPLUGIN += qsvg

#TODO a change in version number does not cause recompilation in the affected source files
#find a way to trigger this and/or don't use a define to specify the patch number.
#perhaps put the build number/version in a file, then add that file to a qrc?
#It might be a good idea to keep the major and minor version numbers as defines,
#but the build number as something that doesn't trigger recompilation.
VERSION = $$system("git describe --long --tags | sed -r 's/([^-]*-g)/\1/;s/-g.*//;s/-/./'")
VERSTR = '\\"$${VERSION}\\"'  # place quotes around the version string
DEFINES += NMVER=\"$${VERSTR}\" # create a VER macro containing the version string

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wwrite-strings \
    -Woverloaded-virtual -Wredundant-decls \
    -Wold-style-cast

# Qt doesn't like these warnings
#QMAKE_CXXFLAGS += -Weffc++ -Wuseless-cast -Wzero-as-null-pointer-constant -Wsign-conversion -Wctor-dtor-privacy -Wshadow

SOURCES += main.cpp \
    beziercurve.cpp \
    document.cpp \
    graphq.cpp \
    heightmap3dexplorer.cpp \
    heightmapfunction.cpp \
    heightmaptextureexplorer.cpp \
    inputlinkq.cpp \
    moduleinputq.cpp \
    moduleoutputq.cpp \
    moduleq.cpp \
    moduletypeq.cpp \
    outputlinkq.cpp \
    rendering/heightmap3drenderer.cpp \
    rendering/heightmapterrainmesh.cpp \
    rendering/heightmaptexturerenderer.cpp \
    rendering/transform3d.cpp \
    typemanagerq.cpp \
    core.cpp

HEADERS += \
    beziercurve.hpp \
    document.hpp \
    graphq.hpp \
    heightmap3dexplorer.hpp \
    heightmapfunction.hpp \
    heightmaptextureexplorer.hpp \
    inputlinkq.hpp \
    moduleinputq.hpp \
    moduleoutputq.hpp \
    moduleq.hpp \
    moduletypeq.hpp \
    outputlinkq.hpp \
    rendering/heightmap3drenderer.hpp \
    rendering/heightmapterrainmesh.hpp \
    rendering/heightmaptexturerenderer.hpp \
    rendering/transform3d.hpp \
    typemanagerq.hpp \
    core.hpp

# Installation path
target.path = /usr/bin
INSTALLS += target

INCLUDEPATH = . ..

LIBS += -L../lib
PRE_TARGETDEPS += ../lib/libnmlib.a
LIBS += -lnmlib

include(deployment.pri)

RESOURCES += \
    nmgui.qrc \
    ../license.qrc

# Additional import path used to resolve QML modules in Creators code model
QML_IMPORT_PATH =
