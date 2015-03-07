import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

TabView {
    id: tabView
    signal moduleSelected(var module)

    function openTabForModuleType(moduleType){
        for(var i = 0; i < tabView.count; ++i){
            if(tabView.getTab(i).item.moduleType === moduleType){
                tabView.currentIndex = i;
                return;
            }
        }
        openNewTabForModuleType(moduleType);
        tabView.currentIndex = tabView.count-1;
    }
    property bool first: true
    function openNewTabForModuleType(moduleType){
        if(!first)return;
        var newTab = tabView.addTab(moduleType.name, moduleTypeEditorTabComponent);
        first = false;
        newTab.active = true;
        newTab.item.moduleType = moduleType;
    }
    
    frameVisible: false
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
        Item {
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
                    onSelectedModuleChanged: {
                        moduleSelected(selectedModule);
                    }
                }
            }
            Loader {
                anchors.fill: parent
                sourceComponent: graphEditorWrapper
                active: moduleType
            }
        }
    }

    Component.onCompleted: openNewTabForModuleType(document.typeManager.userTypes[0]);
}
