import QtQuick 2.2

Rectangle {
    Style { id:mystyle }
    width: 800
    height: 600
    TopBar {
        id: menu
        z: 100
    }

    ModuleTypeBrowser {
        id: moduleTypeBrowser
    }

    GraphEditor{
        anchors.top: menu.bottom
        anchors.left: moduleTypeBrowser.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        TexturePreview{}
        Node{module:mockModule}
        Node{x: 300; y: 100; module:mockModule2}
        Node{module:mockModule3}
        Node{x: 100; y: 100; module:debugInput}
        Node{x: 400; y: 100; module:debugOutput}
    }
}
