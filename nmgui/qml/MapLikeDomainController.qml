import QtQuick 2.2

Item {
    id: mapLikeDomainController
    property var size: Qt.point(0,0) //using var instead of rect, because we need reference semantics instead of value semantics
    property var center: Qt.point(1,1) //using var instead of rect, because we need reference semantics instead of value semantics
    property alias pressed: mouseArea.pressed
    signal doubleClicked(var mouse)
    Item {
        id:offset
        onXChanged: {
            center.x = -x * size.x / parent.width;
        }
        onYChanged: {
            center.y = y * size.y / parent.height;
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: offset
        hoverEnabled: true
        onWheel: {
            wheel.accepted = true;
            //TODO: use wheel.pixelDelta
            size.x *= 1.0 + -wheel.angleDelta.y/1200;
            size.y *= 1.0 + -wheel.angleDelta.y/1200;
            
            offset.x = -center.x * parent.width / size.x;
            offset.y = center.y * parent.height / size.y;
        }
        onDoubleClicked: mapLikeDomainController.doubleClicked(mouse)
    }
}
