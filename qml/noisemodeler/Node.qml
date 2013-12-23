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
            font.pointSize: mystyle.smallTextSize
            color: mystyle.textColor
            anchors.verticalCenter: parent.Center
        }
    }
    Row{
        id: nodeContents
        property int minWidth: childrenRect.width + 2 * horizontalMargins
        property int minHeight: childrenRect.height + 2 * verticalMargins
        property int horizontalMargins: 0
        property int verticalMargins: 6

        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: verticalMargins
        anchors.bottomMargin: verticalMargins
        anchors.leftMargin: horizontalMargins
        anchors.rightMargin: horizontalMargins
        spacing: 5
        Column{
            Repeater{
                model: ['position','lacunarity','gain']
                NodeInput{labelText:modelData}
            }
        }
        Column{
            Repeater{
                model: ['value', 'test']
                NodeOutput{labelText:modelData}
            }
        }
    }
}
