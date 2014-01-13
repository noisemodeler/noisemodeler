import QtQuick 2.0
import NoiseModeler 1.0

Item {
    property ModuleOutput model
    height: mystyle.node.connectorHeight
    width: connector.width + connectorDescription.width
    anchors.right: parent.right

    Connector {
        id: connector
        anchors.right: parent.right
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.right: connector.left
        horizontalAlignment: Text.AlignRight
        text: model.name
    }
}
