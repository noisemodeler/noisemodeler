import QtQuick 2.2
import QtQuick.Window 2.1
import NoiseModeler 1.0

Rectangle {
    Style { id:mystyle }
    width: 1024
    height: 600
    TopBar {
        id: menu
        z: 100
    }

    ModuleTypeBrowser {
        z:50
        id: moduleTypeBrowser
    }

    Item {
        id: mainArea
        anchors.top: menu.bottom
        anchors.left: moduleTypeBrowser.right
        anchors.right: inspectorArea.left
        anchors.bottom: parent.bottom
    }

    Item {
        property bool active: true
        id: inspectorArea
        anchors.top: menu.bottom
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
        module: editor.selectedModule
    }

    GraphEditor {
        id: editor
        anchors.fill: mainArea
        graph: mockGraph
    }
    Keys.onPressed: {
        if(event.key === Qt.Key_F){
            editor.autoArrangeWindows();
        }
    }
//    Window{
//        title: "Heightmap terrain preview"
//        width: 400
//        height: 400
//        visible:true
//        HeightMap3DExplorer {
//            id: heightMapExplorer
//            heightMapFunction: HeightMapFunction{
//                outputLink: debugOutput.outputs[0]
//                inputLink: debugInput.inputs[0]
//            }
//            anchors.fill: parent
//        }
//    }
}
