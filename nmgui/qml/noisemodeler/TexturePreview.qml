import QtQuick 2.0
import NoiseModeler 1.0

SubWindow {
    color:'black'
    windowTitle: "texture preview"

    contents.width: 100
    contents.height: 100
    contents.children: [
        TextureRenderer{
            anchors.fill: parent
            SequentialAnimation on t {
                NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
                NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
                loops: Animation.Infinite
                running: true
            }
        }
    ]
}
