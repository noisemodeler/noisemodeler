import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

ApplicationWindow {
    Style { id: mystyle }
    visible: true
    width: Screen.desktopAvailableWidth * 0.8
    height: Screen.desktopAvailableHeight * 0.8
    title: "Noise Modeler"

    Rectangle {
        id: mainWindow
        property variant currentModuleType: document.typeManager.userTypes[0]

        //layout
        Item {
            id: mainArea
            anchors.top: topBar.bottom
            anchors.left: moduleTypeBrowser.right
            anchors.right: inspectorArea.left
            anchors.bottom: parent.bottom
        }

        Item {
            id: inspectorArea
            property bool active: true
            anchors.top: topBar.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            width: active ? mystyle.inspector.width : 0
        }

        Item {
            id: browserArea
            z: 50
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: topBar.bottom
        }

        //dialogs
        AboutDialog { id: aboutDialog }
        OpenDialog { id: openDialog }
        SaveDialog { id: saveDialog }



        TopBar { id: topBar }
        ModuleTypeBrowser {
            id: moduleTypeBrowser
            anchors.fill: browserArea
            onAddModuleClicked: {
                currentModuleType.graph.createModule(moduleType);
            }
            onEditModuleTypeClicked: {
                currentModuleType = moduleType;
                //TODO open a new tab if not open
            }
            onInspectModuleTypeClicked: {
                inspector.inspectModuleType(moduleType);
            }
        }

        Inspector {
            id: inspector
            anchors.fill: inspectorArea
            z: 50
        }

        ModuleTypeTabView {
            id: moduleTypeTabView
            onModuleSelected: inspector.inspectModule
        }

        //eventhandlers
        onCurrentModuleTypeChanged: moduleTypeTab.openTabForModuleType
    }
}
