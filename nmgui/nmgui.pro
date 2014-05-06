# Add more folders to ship with the application, here
folder_01.source = qml/noisemodeler
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creators code model
QML_IMPORT_PATH =

TARGET = nmgui
QT += qml svg

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wwrite-strings -fshort-enums \
    -Woverloaded-virtual -Wredundant-decls \
    -Wold-style-cast

# Qt doesn't like these warnings
#QMAKE_CXXFLAGS += -Weffc++ -Wuseless-cast -Wzero-as-null-pointer-constant -Wsign-conversion -Wctor-dtor-privacy -Wshadow

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    moduleq.cpp \
    outputlinkq.cpp \
    inputlinkq.cpp \
    beziercurve.cpp \
    moduletypeq.cpp \
    moduleinputq.cpp \
    moduleoutputq.cpp \
    graphq.cpp \
    typemanagerq.cpp \
    rendering/transform3d.cpp \
    rendering/heightmapterrainmesh.cpp \
    heightmapviewportrenderer.cpp \
    heightmapfunction.cpp \
    heightmap3dexplorer.cpp \
    heightmaptextureexplorer.cpp \
    rendering/heightmap3drenderer.cpp \
    rendering/heightmaptexturerenderer.cpp \
    document.cpp

HEADERS += \
    moduleq.hpp \
    outputlinkq.hpp \
    inputlinkq.hpp \
    beziercurve.hpp \
    moduletypeq.hpp \
    moduleinputq.hpp \
    moduleoutputq.hpp \
    graphq.hpp \
    typemanagerq.hpp \
    rendering/transform3d.hpp \
    rendering/heightmapterrainmesh.hpp \
    heightmapviewportrenderer.hpp \
    heightmapfunction.hpp \
    heightmap3dexplorer.hpp \
    heightmaptextureexplorer.hpp \
    rendering/heightmap3drenderer.hpp \
    rendering/heightmaptexturerenderer.hpp \
    document.hpp

# Installation path
# target.path =

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib

PRE_TARGETDEPS += ../nmlib/libnmlib.a

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    nmgui.qrc

OTHER_FILES += \
    qml/noisemodeler/ToolBarIcon.qml

