import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

Rectangle {
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
        anchors.top: topBar.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: inspector.visible ? mystyle.inspector.width : 0;
    }
    
    Item {
        id: browserArea
        z: 50
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: topBar.bottom
        width: mystyle.dp * 200
    }
    
    //dialogs
    AboutDialog { id: aboutDialog }
    OpenDialog { id: openDialog }
    SaveDialog { id: saveDialog }
    SettingsDialog { id: settingsDialog }
    
    TopBar { id: topBar }
    ModuleTypeBrowser {
        id: moduleTypeBrowser
        anchors.fill: browserArea
        onAddModuleClicked: {
            currentModuleType.graph.createModule(moduleType);
        }
        onEditModuleTypeClicked: {
            currentModuleType = moduleType;
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
        anchors.fill: mainArea
        onModuleSelected: {
            inspector.inspectModule(module);
        }
    }
    
    //eventhandlers
    onCurrentModuleTypeChanged: {
        moduleTypeTabView.openTabForModuleType(currentModuleType);
    }
}
