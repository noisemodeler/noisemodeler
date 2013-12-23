import QtQuick 2.0

Item {
    property alias labelText: connectorDescription.text
    height: 30
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
    }
}
