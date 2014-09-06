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
    id: window
    width: Screen.desktopAvailableWidth * 0.8
    height: Screen.desktopAvailableHeight * 0.8
    title: "Noise Modeler"

    //hacky way of reloading when a new document is opened
    StackView {
        id: stackView
        anchors.fill: parent
        Component.onCompleted: { push(documentEditor); }
        Connections {
            target: document
            onTypeManagerChanged: {
                stackView.clear();
                stackView.push(documentEditor);
            }
        }
    }

    Component{
        id: documentEditor
        Rectangle {
            id: mainWindow
            property variant currentModuleType: document.typeManager.userTypes[0]

            AboutDialog { id: aboutDialog }

            OpenDialog { id: openDialog }

            SaveDialog { id: saveDialog }

            TopBar { id: topBar }

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
                    currentModuleType = moduleType;
                    //TODO open a new tab if not open
                }
                onInspectModuleTypeClicked: {
                    inspector.inspectModuleType(moduleType);
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
                width: active ? mystyle.inspector.width : 0
            }

            Inspector {
                id: inspector
                anchors.fill: inspectorArea
                z: 50
            }

            TabView {
                id: tabView
                Connections{
                    target: mainWindow
                    onCurrentModuleTypeChanged: {
                        tabView.openTabForModuleType(currentModuleType);
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
                Component {
                    id: moduleTypeEditorTabComponent
                    Item{
                        property variant moduleType
                        Component {
                            id: graphEditorWrapper
                            GraphEditor {
                                anchors.fill: parent
                                graph: moduleType.graph
                                onVisibleChanged: {
                                    if(visible){
                                        currentModuleType = moduleType;
                                        if(selectedModule !== undefined)inspector.inspectModule(selectedModule);
                                    }
                                }
                                onSelectedModuleChanged: inspector.inspectModule(selectedModule);
                            }
                        }
                        Loader {
                            anchors.fill: parent
                            sourceComponent: graphEditorWrapper
                            active: moduleType
                        }
                    }
                }
                function openTabForModuleType(moduleType){
                    for(var i=0; i<tabView.count; ++i){
                        if(tabView.getTab(i).item.moduleType===moduleType){
                            tabView.currentIndex = i;
                            return;
                        }
                    }
                    openNewTabForModuleType(moduleType);
                    tabView.currentIndex = tabView.count-1;
                }

                function openNewTabForModuleType(moduleType){
                    var newTab = tabView.addTab(moduleType.name, moduleTypeEditorTabComponent);
                    newTab.active = true;
                    newTab.item.moduleType = moduleType;
                }

                Component.onCompleted: openNewTabForModuleType(document.typeManager.userTypes[0]);
            }
        }
    }
}
