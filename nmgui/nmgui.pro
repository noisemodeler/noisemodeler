# Add more folders to ship with the application, here
folder_01.source = qml/noisemodeler
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creators code model
QML_IMPORT_PATH =

TARGET = nmgui
QT += qml

QMAKE_CXXFLAGS += -std=c++11 \
    -Wall -Werror -Wextra \
    -pedantic-errors -Wwrite-strings -fshort-enums \
    -Woverloaded-virtual -Wredundant-decls \
    -Wold-style-cast

# Qt doesn't like these warnings
#QMAKE_CXXFLAGS += -Weffc++ -Wuseless-cast -Wzero-as-null-pointer-constant -Wsign-conversion -Wctor-dtor-privacy -Wshadow

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    texturerenderer.cpp \
    moduleq.cpp \
    outputlinkq.cpp \
    inputlinkq.cpp

HEADERS += \
    texturerenderer.hpp \
    moduleq.hpp \
    outputlinkq.hpp \
    inputlinkq.hpp

# Installation path
# target.path =

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib

PRE_TARGETDEPS += ../nmlib/libnmlib.a

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/noisemodeler/SubWindow.qml

