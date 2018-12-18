import QtQuick 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Page {
    id: page

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

    header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        Repeater {
            model: swipeView.count
            TabButton {
                text: swipeView.itemAt(index).moduleType.name
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

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
