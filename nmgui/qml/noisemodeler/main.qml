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
        anchors.right: parent.right
        anchors.bottom: parent.bottom
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
//        HeightMapRenderer {
//            id: textureRenderer
//            outputLink: debugOutput.outputs[0]
//            inputLink: debugInput.inputs[0]
//            anchors.fill: parent
//        }
//        MapLikeDomainController {
//            domain: textureRenderer.domain
//            anchors.fill: textureRenderer
//        }
//    }
}
