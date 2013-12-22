import QtQuick 2.2

Rectangle {
    id: node
    property alias nodeName: nodeLabel.text
    property alias hover: nodeMouseArea.containsMouse
    property real minWidth: Math.max(50, nodeContents.minWidth)
    property real minHeight: header.height + nodeContents.minHeight
    width: minWidth
    height: minHeight
    border.color: mystyle.borderColor
    color:mystyle.node.bgColor
    border.width: 1
    radius: 3
    smooth: true
    MouseArea {
        id: nodeMouseArea

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        onClicked: console.log("Hello world!")
        hoverEnabled: true
        drag.target: parent
        drag.minimumY: 0
        drag.minimumX: 0
        drag.maximumX: graphEditor.width - node.width
        drag.maximumY: graphEditor.height - node.height
    }
    Rectangle{
        id:header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 13
        border.width: 1
        border.color: mystyle.borderColor
        color: mystyle.bgColor
        Text {
            x: 3
            id: nodeLabel
            text: 'Perlin'
            font.pointSize: 8
            color: mystyle.textColor
            anchors.verticalCenter: parent.Center
        }
    }
    Rectangle{
        id: nodeContents
        property int minWidth:100
        property int minHeight:100
        color:"white"
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 6
        anchors.bottomMargin: 6
        anchors.leftMargin: 2
        anchors.rightMargin: 2
    }
}
