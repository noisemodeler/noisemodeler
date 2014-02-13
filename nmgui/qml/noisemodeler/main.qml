import QtQuick 2.2

Rectangle {
    Style { id:mystyle }
    width: 800
    height: 600
    TopBar {
        id: menu
    }

    GraphEditor{
        anchors.top: menu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        TexturePreview{}
        Node{module:mockModule}
        Node{module:mockModule2}
        Node{module:mockModule3}
        Node{module:debugInput}
        Node{module:debugOutput}
    }
}
