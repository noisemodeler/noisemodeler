import QtQuick 2.0
import NoiseModeler 1.0

SubWindow {
    color:'black'
    windowTitle: "texture preview"

    contents.width: 200
    contents.height: 200
    contents.children: [
        TextureRenderer{
            inputLink: debugOutput.inputs[0]
            outputLink: debugInput.outputs[0]
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
