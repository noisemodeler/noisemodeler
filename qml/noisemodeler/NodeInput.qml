import QtQuick 2.2
import NoiseModeler 1.0

Item {
    property ModuleInput model
    height: mystyle.node.connectorHeight
    width: connector.width + connectorDescription.width
    Connector {
        id: connector
        anchors.left: parent.left
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
        text:model.name
    }
}
