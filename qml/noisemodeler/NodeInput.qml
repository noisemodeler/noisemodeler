import QtQuick 2.2

Item {
    property alias labelText: connectorDescription.text
    height: 30
    width: childrenRect.width
    Connector {
        id: connector
        anchors.left: parent.left
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
    }
}
