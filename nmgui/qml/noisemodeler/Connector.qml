import QtQuick 2.2

Rectangle {
    property bool connected: false
    property int dimensions: 1
    anchors.verticalCenter: parent.verticalCenter
//    border.color: mystyle.borderColor
    border.width: 0
    height: 8
    width: 8
    color: connected ? mystyle.connector.connectedColors[dimensions-1] : mystyle.connector.disconnectedColors[dimensions-1]
}
