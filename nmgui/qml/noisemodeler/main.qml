import QtQuick 2.2

Rectangle {
    Style { id:mystyle }
    width: 800
    height: 600
    Rectangle {
        id:menu
        color: mystyle.topBar.bgColor
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Text {
            color: "#cccccc"
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: "File"
            verticalAlignment: Text.AlignVCenter
        }
    }

    GraphEditor{
        anchors.top: menu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
