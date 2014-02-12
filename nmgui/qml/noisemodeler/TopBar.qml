import QtQuick 2.2

Rectangle {
    color: mystyle.topBar.bgColor
    height: 40
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    Row{
        anchors.fill: parent
        TopBarButton {
            text: "Menu"
        }
    }
}
