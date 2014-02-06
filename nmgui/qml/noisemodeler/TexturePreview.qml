import QtQuick 2.0
import NoiseModeler 1.0

Rectangle {
    color:'black'
    width: 100
    height: 62
    MouseArea{
        anchors.fill: parent
        drag.target: parent
    }

    TextureRenderer{
        anchors.fill: parent
        SequentialAnimation on t {
            NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
            NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
            loops: Animation.Infinite
            running: true
        }
    }
}
