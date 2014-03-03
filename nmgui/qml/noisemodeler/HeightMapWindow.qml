import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Layouts 1.1

SubWindow {
    windowTitle: "heightmap preview"
    contents.width: 200
    contents.height: 200
    contents.children: [
        HeightMapRenderer {
            id:textureRenderer
            outputLink: debugOutput.outputs[0]
            inputLink: debugInput.inputs[0]
            anchors.fill: parent
            SequentialAnimation on t {
                NumberAnimation { to: 1; duration: 2500; easing.type: Easing.InQuad }
                NumberAnimation { to: 0; duration: 2500; easing.type: Easing.OutQuad }
                loops: Animation.Infinite
                running: true
            }
        },
        GridLayout {
            anchors.top: textureRenderer.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 4
            Text {
                text: "x:"
            }
            LineInput {
                text:"0"
                validator: DoubleValidator{}
                onNewAcceptableValue: {
                    textureRenderer.domain.x = parseFloat(text);
                }
            }
            Text {
                text: "width:"
            }
            LineInput {
                text:"1"
                validator: DoubleValidator{}
                onNewAcceptableValue: {
                    textureRenderer.domain.width = parseFloat(text);
                }
            }
            Text {
                text: "y:"
            }
            LineInput {
                text:"0"
                validator: DoubleValidator{}
                 onNewAcceptableValue: {
                    textureRenderer.domain.y = parseFloat(text);
                }
           }
            Text {
                text: "height:"
            }
            LineInput {
                text:"1"
                validator: DoubleValidator{}
                onNewAcceptableValue: {
                    textureRenderer.domain.height = parseFloat(text);
                }
            }

        }
    ]
}
