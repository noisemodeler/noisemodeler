import QtQuick 2.2
import CustomGeometry 1.0

Item {
    property alias from: curve.p1
    property alias to: curve.p4
    property real fromAngle: 0
    property real toAngle: Math.PI
    property real weight: 100 * mystyle.dp
    property alias strokeColor: curve.strokeColor
    QtBezierCurve{
        lineWidth: 2 * mystyle.dp
        id:curve
        p2.x: from.x + Math.cos(fromAngle) * weight
        p2.y: from.y + Math.sin(fromAngle) * weight
        p3.x: to.x + Math.cos(toAngle) * weight
        p3.y: to.y + Math.sin(toAngle) * weight
    }

}
