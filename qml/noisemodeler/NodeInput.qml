import QtQuick 2.2
import NoiseModeler 1.0

Item {
    property ModuleInput model
    height: mystyle.node.connectorHeight
    width: connector.width + connectorDescription.width
    Connector {
        id: connector
        anchors.left: parent.left
        DropArea{
            id:dropArea
            anchors.fill: parent
            anchors.margins: -4
            Rectangle{
                anchors.fill: parent
                anchors.margins: 4+1
                color: "blue"
                visible: dropArea.containsDrag
            }
            onDropped: {
                console.log("Dropped");
                model.name = "GRAAAWL";
            }
        }
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
        text:model.name
    }

}
