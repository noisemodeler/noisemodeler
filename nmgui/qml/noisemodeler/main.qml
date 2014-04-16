import QtQuick 2.2
import QtQuick.Window 2.1
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: mainWindow
    property ModuleType currentModuleType: typeManager.userTypes[0]
    Style { id: mystyle }
    width: 1024
    height: 600

    Rectangle {
        color: mystyle.topBar.bgColor
        id: topBar
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    ModuleTypeBrowser {
        z: 50
        id: moduleTypeBrowser
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: topBar.bottom
        onAddModuleClicked: {
            currentModuleType.graph.createModule(moduleType);
        }
        onEditModuleTypeClicked: {
            //TODO open a new tab or open an existing one
            currentModuleType = moduleType;
            console.log(moduleType.name);
        }
    }

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
        width: active ? 200 : 0
    }

    Rectangle {
        id: inspector
        color: mystyle.inspector.bgColor
        anchors.fill: inspectorArea
    }

    ModuleInspector {
        id: moduleInspector
        z: 50
        anchors.fill: inspectorArea
    }

    TabView {
        id: tabView
        Connections{
            target: mainWindow
            onCurrentModuleTypeChanged: {
                for(var i=0; i<tabView.count; ++i){
                    if(tabView.getTab(i).moduleType===currentModuleType){
                        tabView.currentIndex = i;
                        return;
                    }
                }
                console.error("No tab with module" + currentModuleType);
            }
        }

        frameVisible: false
        anchors.fill: mainArea
        anchors.topMargin: -topBar.height
        style: TabViewStyle {
            frameOverlap: 0
            tabsMovable: true
            tab: TabButton {
                text: styleData.title
                implicitWidth: width
                implicitHeight: height
                active: styleData.selected
            }
        }
        Repeater{
            model: typeManager.userTypes
            ModuleTypeEditorTab {
                moduleType: modelData
                onVisibleChanged: if(visible)currentModuleType = modelData;
                onSelectedModuleChanged: moduleInspector.module = selectedModule;
            }
        }
    }
}
