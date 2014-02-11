import QtQuick 2.2
import NoiseModeler 1.0

Item {
    id:nodeOutput
    property InputLink model
    height: mystyle.connector.height
    width: connector.width + connectorDescription.width

    Connector {
        id: connector
        connected: model.outputLink
        dimensionality: model.dimensionality
        anchors.left: parent.left
        DropArea{
            id:dropArea
            anchors.fill: parent
            anchors.margins: -connector.width/2
            keys: [model.dimensionality]
            Rectangle{
                anchors.centerIn: parent
                width: connector.width
                height: connector.height
                color: "blue"
                visible: dropArea.containsDrag
            }
            onDropped: {
                var nodeOutput = drag.source.parent.parent;
                model.outputLink = nodeOutput.model;
                curve.otherConnector = nodeOutput.connector;
            }
        }
        WeightedAngleCurve{
            property Connector otherConnector
            id: curve
            to.x: 0
            to.y: parent.height/2
            visible: model.outputLink
            function updateFrom(){
                if(!otherConnector)return;
                from.x = mapFromItem(otherConnector,0,0).x+otherConnector.width;
                from.y = mapFromItem(otherConnector,0,0).y+otherConnector.height/2;
            }
            onOtherConnectorChanged: {
                if(!otherConnector)return;
                otherConnector.parent.parent.parent.parent.parent.xChanged.connect(updateFrom);
                otherConnector.parent.parent.parent.parent.parent.yChanged.connect(updateFrom);
                updateFrom();
            }
            Component.onCompleted: {
                nodeOutput.parent.parent.parent.parent.yChanged.connect(updateFrom);
                nodeOutput.parent.parent.parent.parent.xChanged.connect(updateFrom);
            }
        }
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.left: connector.right
        text:model.name
    }

}
