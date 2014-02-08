import QtQuick 2.2
import NoiseModeler 1.0

Item {
    property ModuleInput model
    height: mystyle.node.connectorHeight
    width: connector.width + connectorDescription.width
    Connector {
        id: connector
        anchors.left: parent.left
        color: model.source ? mystyle.node.connectorColor : Qt.darker(mystyle.node.connectorColor, 2)
        DropArea{
            id:dropArea
            anchors.fill: parent
            anchors.margins: -connector.width/2
            Rectangle{
                anchors.centerIn: parent
                width: connector.width
                height: connector.height
                color: "blue"
                visible: dropArea.containsDrag
            }
            onDropped: {
                model.outputLink = drag.source.parent.parent.model;
            }
        }
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
        text:model.name
    }

}
