import QtQuick 2.2
import NoiseModeler 1.0

Item {
    id:nodeOutput
    property variant model
    property alias connector: connector
    height: mystyle.connector.height
    width: connector.width + connectorDescription.width + 5 //mystery magical number, added it because I couldn't figure out why stuff didn't align

    Connector {
        id: connector
        property alias otherConnector: curve.otherConnector
        connected: model.outputLink
        dimensionality: model.dimensionality
        tipXdirection: -1
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
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onPressed: model.outputLink = null
        }

        WeightedAngleCurve{
            id: curve
            property Connector otherConnector
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
        text: model.name
    }

}
