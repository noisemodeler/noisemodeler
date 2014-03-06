import QtQuick 2.2
import QtQuick.Window 2.1
import NoiseModeler 1.0

Item {
    id: mapLikeDomainController
    property var domain: Qt.rect(0,0,1,1) //using var instead of rect, because we need reference semantics instead of value semantics
    Item {
        id:offset
        onXChanged: {
            domain.x = -x * domain.width / parent.width;
        }
        onYChanged: {
            domain.y = -y * domain.height / parent.height;
        }
    }
    MouseArea {
        anchors.fill: parent
        drag.target: offset
        hoverEnabled: true
        onWheel: {
            wheel.accepted = true;
            //TODO: use wheel.pixelDelta
            domain.width *= 1.0 + -wheel.angleDelta.y/1200;
            domain.height *= 1.0 + -wheel.angleDelta.y/1200;
            
            offset.x = -domain.x * parent.width / domain.width;
            offset.y = -domain.y * parent.height / domain.height;
        }
    }
}
