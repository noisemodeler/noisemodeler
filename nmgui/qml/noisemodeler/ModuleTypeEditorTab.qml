import QtQuick 2.2
import QtQuick.Window 2.1
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

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
