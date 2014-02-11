import QtQuick 2.0
import NoiseModeler 1.0

Item {
    id: nodeOutput
    property OutputLink model
    property alias connector: connector
    height: mystyle.connector.height
    width: connector.width + connectorDescription.width
    anchors.right: parent.right

    Connector {
        id: connector
        connected: model.links.length > 0
        dimensionality: model.dimensionality
        tipXdirection: 1
        anchors.right: parent.right
        MouseArea {
            id: dragArea
            anchors.fill: parent
            drag.target: dragDummy
            onReleased: {
                drag.target.Drag.drop();
                drag.target.x=drag.target.y=0;
            }
            WeightedAngleCurve {
                from.x: parent.width
                from.y: parent.height/2
                to.x: dragDummy.x
                to.y: dragDummy.y + dragDummy.height/2
                visible: dragArea.drag.active
                strokeColor: mystyle.linkStrokeColor
            }
            drag.threshold: 0
        }
        Rectangle{
            id: dragDummy
            color: parent.color
            visible: Drag.active
            width: parent.width-2
            height: parent.height-2
            Drag.active: dragArea.drag.active
            Drag.hotSpot.x: width/2
            Drag.hotSpot.y: height/2
            Drag.keys: [model.dimensionality]
        }
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.right: connector.left
        horizontalAlignment: Text.AlignRight
        text: model.name
    }
}
