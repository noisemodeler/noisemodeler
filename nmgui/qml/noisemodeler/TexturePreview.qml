import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Layouts 1.1

SubWindow {
    windowTitle: "texture preview"
    contents.width: 350
    contents.height: 350
    contents.children: [
        HeightMapRenderer {
            id:textureRenderer
            outputLink: debugOutput.outputs[0]
            inputLink: debugInput.inputs[0]
            anchors.fill: parent
            onDomainChanged: {
                xPosInput.text = domain.x.toFixed(3);
                yPosInput.text = domain.y.toFixed(3);
                widthInput.text = domain.width.toFixed(3);
                heightInput.text = domain.height.toFixed(3);
            }
        },
        MapLikeDomainController {
            domain: textureRenderer.domain
            anchors.fill: textureRenderer
        },
        GridLayout {
            anchors.top: textureRenderer.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 4
            Text {
                text: "x:"
            }
            LineInput {
                id: xPosInput
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
                id: widthInput
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
                id: yPosInput
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
                id: heightInput
                text:"1"
                validator: DoubleValidator{}
                onNewAcceptableValue: {
                    textureRenderer.domain.height = parseFloat(text);
                }
            }

        }
    ]
}
