import QtQuick 2.2

Item{
    property alias labelText: connectorDescription.text
    height: 30
    width: childrenRect.width
        Rectangle{
            id: connector
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            border.color: mystyle.borderColor
            height: 10
            width:10
            color: mystyle.node.connectorColor
        }

        ConnectorDescription{
            id: connectorDescription
        }
}
