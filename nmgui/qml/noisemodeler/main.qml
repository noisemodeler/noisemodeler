import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1

Item {
    id: window
    width: 1024
    height: 600

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
            Style { id: mystyle }

            FileDialog {
                id: openDialog
                title: "Open file"
                onAccepted: {
                    console.log("TODO: open " + openDialog.fileUrl);
                    document.openQmlUrl(openDialog.fileUrl);
                }
                nameFilters: ["Noise Modeler graphs (*.nm.json)", "All files (*)"]
            }
            FileDialog {
                id: saveDialog
                title: "Save file"
                onAccepted: {
                    //TODO enforce correct extension
                    document.saveAsQmlUrl(saveDialog.fileUrl);
                }
                selectExisting: false
                nameFilters: ["Noise Modeler graphs (*.nm.json)", "All files (*)"]
            }

            Rectangle {
                color: mystyle.topBar.bgColor
                id: topBar
                height: 40
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                RowLayout{
                    anchors.fill: parent
                    Item{
                        width: 5
                    }
                    ToolBarIcon{
                        Layout.alignment: Qt.AlignLeft
                        source: 'qrc:///icons/save.svg'
                        onClicked: saveDialog.open();
                        toolTipText: "Save"
                    }
                    ToolBarIcon{
                        Layout.alignment: Qt.AlignLeft
                        source: 'qrc:///icons/open.svg'
                        onClicked: openDialog.open();
                        toolTipText: "Open"
                    }
                    Item {
                        Layout.fillWidth: true
                    }
                }
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
                    currentModuleType = moduleType;
                    //TODO open a new tab if not open
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
                                        if(selectedModule !== undefined)moduleInspector.module = selectedModule;
                                    }
                                }
                                onSelectedModuleChanged: moduleInspector.module = selectedModule;
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
