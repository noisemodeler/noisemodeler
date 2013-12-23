import QtQuick 2.2

Item{
    property alias labelText: nodeInputLabel.text
    height: 30
    width: childrenRect.width
        Rectangle{
            id: connector
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            border.color: 'black'
            height: 10
            width:10
            color: 'red'
        }

        Text{
            id: nodeInputLabel
            width: 40
            anchors.left: connector.right
//            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 3
            text: 'pos'
        }
}
