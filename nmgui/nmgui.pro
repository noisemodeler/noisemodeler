# Add more folders to ship with the application, here
folder_01.source = qml/noisemodeler
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creators code model
QML_IMPORT_PATH =

TARGET = nmgui
QT += qml

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    module.cpp \
    moduleinput.cpp \
    moduleoutput.cpp

HEADERS += \
    module.h \
    moduleinput.h \
    moduleoutput.h

# Installation path
# target.path =

INCLUDEPATH = . ..

LIBS += -L../nmlib -lnmlib

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

