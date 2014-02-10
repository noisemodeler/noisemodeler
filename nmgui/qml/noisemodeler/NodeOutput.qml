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
        MouseArea {
            id:dragArea
            anchors.fill: parent
            drag.target: dragDummy
            onReleased: {
                drag.target.Drag.drop();
                drag.target.x=drag.target.y=0;
            }
            onPressed: {
                console.log("Starged dragging")
            }
            WeightedAngleCurve{
                from.x: parent.width
                from.y: parent.height/2
                to.x: dragDummy.x
                to.y: dragDummy.y + dragDummy.height/2
                visible: dragArea.drag.active
            }

            drag.threshold: 0
        }
        Rectangle{
            id:dragDummy
            color:parent.color
            visible: Drag.active
            width:parent.width-2
            height:parent.height-2
            Drag.active: dragArea.drag.active
            Drag.hotSpot.x: width/2
            Drag.hotSpot.y: height/2
        }
    }

    ConnectorDescription {
        id: connectorDescription
        anchors.right: connector.left
        horizontalAlignment: Text.AlignRight
        text: model.name
    }
}
