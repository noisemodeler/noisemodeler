import QtQuick 2.2
import QtQuick.Controls 1.1

Tab {
    id: moduleTypeEditorTab
    property ModuleType moduleType
    property variant selectedModule
    title: moduleType.name
    GraphEditor {
        id: graphEditor
        graph: moduleType.graph
        onSelectedModuleChanged: moduleTypeEditorTab.selectedModule = selectedModule;
    }
}
