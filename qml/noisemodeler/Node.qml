import QtQuick 2.2

Rectangle {
    id: node
    property alias nodeName: nodeLabel.text
    property alias hover: nodeMouseArea.containsMouse
    property real connectorSpacing: 8
    property real padding: 5
    width: 80
    height: 80
    color: hover ? Qt.lighter(mystyle.bgColor, 1.7) : Qt.lighter(mystyle.bgColor, 1.4)
    border.color: mystyle.borderColor
    border.width: 1
    radius: 3
    smooth: true
    MouseArea {
        id: nodeMouseArea
        anchors.fill: parent
        onClicked: buttonClick()
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
        height: 14
        border.width: 1
        border.color: mystyle.borderColor
        color: mystyle.bgColor
        Text {
            x: 3
            id: nodeLabel
            text: 'Perlin'
            font.pointSize: 8
            color: mystyle.textColor
        }
    }
    Item {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        Column {
            id: inputsColumn
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            spacing:node.connectorSpacing
            //InputNodeConnector{}
            //InputNodeConnector{}
//            InputNodeConnector{}
//            InputNodeConnector{}
        }
        Item {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: inputsColumn.right
            anchors.right: outputsColumn.left
            Rectangle {
                id:nodePreview
                width: height
                height: parent.height - 4
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 1
            }
        }
        Column {
            id: outputsColumn
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            spacing:node.connectorSpacing
//            OutputNodeConnector{}
//            OutputNodeConnector{}
        }
    }
}
