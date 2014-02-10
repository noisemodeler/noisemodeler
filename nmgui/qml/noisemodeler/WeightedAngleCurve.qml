import QtQuick 2.0
import CustomGeometry 1.0

Item {
    property alias from: curve.p1
    property alias to: curve.p4
    property real fromAngle: 0
    property real toAngle: Math.PI
    property real weight: 100
    property alias strokeColor: curve.strokeColor
    QtBezierCurve{
        id:curve
        p2.x: from.x + Math.cos(fromAngle) * weight
        p2.y: from.y + Math.sin(fromAngle) * weight
        p3.x: to.x + Math.cos(toAngle) * weight
        p3.y: to.y + Math.sin(toAngle) * weight
    }

}
