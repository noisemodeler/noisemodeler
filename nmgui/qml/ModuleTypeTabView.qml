import QtQuick 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Item {
    signal moduleSelected(var module)

    function openTabForModuleType(moduleType){
        for(var i = 0; i < swipeView.count; ++i){
            if(swipeView.itemAt(i).moduleType === moduleType){
                swipeView.currentIndex = i;
                return;
            }
        }
        openNewTabForModuleType(moduleType);
        //TODO: switch to tab
    }

    function openNewTabForModuleType(moduleType){
        swipeView.addItem(moduleTypeEditorTabComponent.createObject(swipeView, {moduleType: moduleType}));
        //TODO: switch to tab
    }

    TabBar {
        id: tabBar
        height: mystyle.topBar.height
        anchors.top: parent.top
        anchors.topMargin: -mystyle.topBar.height
        currentIndex: swipeView.currentIndex
        background: Item {}
        Repeater {
            model: swipeView.count
            NmTabButton {
                text: swipeView.itemAt(index).moduleType.name
                active: swipeView.currentIndex === index
                anchors.bottom: parent.bottom
                anchors.top: parent.top
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false

        Component {
            id: moduleTypeEditorTabComponent
            Item {
                property variant moduleType
                Component {
                    id: graphEditorComponent
                    GraphEditor {
                        graph: moduleType.graph
                        onVisibleChanged: {
                            if(visible){
                                currentModuleType = moduleType;
                                if(selectedModule !== undefined)inspector.inspectModule(selectedModule);
                            }
                        }
                        onSelectedModuleChanged: {
                            moduleSelected(selectedModule);
                        }
                    }
                }
                Loader {
                    anchors.fill: parent
                    sourceComponent: graphEditorComponent
                    active: moduleType
                }
            }
        }
    }

}
