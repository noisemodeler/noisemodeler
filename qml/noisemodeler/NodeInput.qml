import QtQuick 2.2

Item {
    property alias labelText: connectorDescription.text
    height: mystyle.node.connectorHeight
    width: connector.width + connectorDescription.width
    Connector {
        id: connector
        anchors.left: parent.left
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
    }
}
