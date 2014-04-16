import QtQuick 2.2
import QtQuick.Window 2.1
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Tab {
    id: moduleTypeEditorTab
    property ModuleType moduleType
    title: moduleType.name
    GraphEditor {
        id: editor
        graph: moduleType.graph
        onSelectedModuleChanged: moduleType.module = module;
    }
    Keys.onPressed: {
        if(event.key === Qt.Key_F){
            editor.autoArrangeWindows();
        }
    }
}
