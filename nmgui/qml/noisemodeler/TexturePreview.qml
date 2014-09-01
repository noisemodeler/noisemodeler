import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Layouts 1.1

SubWindow {
    property bool maximized: false
    windowTitle: "texture preview"
    contents.width: maximized ? mainArea.width : 350 * mystyle.dp
    contents.height: maximized ? mainArea.height - topBar.height - titleHeight: 350 * mystyle.dp //TODO fix this ugly dependency
    z: maximized ? 20 : 0
    contents.children: [
        HeightMapTextureExplorer {
            id: textureRenderer
            heightMapFunction: HeightMapFunction {
                inputLink: document.typeManager.userTypes[0].graph.findModule("inputs").inputs[0];
                outputLink: document.typeManager.userTypes[0].graph.findModule("outputs").outputs[0];
            }
            anchors.fill: parent
        },
        MapLikeDomainController {
            size: textureRenderer.size
            center: textureRenderer.center
            anchors.fill: textureRenderer
            onPressedChanged: textureRenderer.focus = true;
            onDoubleClicked: maximized = !maximized;
        },
        GridLayout {
            anchors.top: textureRenderer.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 4
            Text {
                font.pixelSize: mystyle.textSize
                text: "x:"
            }
            ScrollableFloatInput {
                monitoredValue: textureRenderer.center.x
                width: 50
                onNewAcceptableValue: textureRenderer.center.x = value;
            }
            Text {
                font.pixelSize: mystyle.textSize
                text: "width:"
            }
            ScrollableFloatInput {
                monitoredValue: textureRenderer.size.x
                width: 50
                onNewAcceptableValue: textureRenderer.size.x = value;
            }
            Text {
                font.pixelSize: mystyle.textSize
                text: "y:"
            }
            ScrollableFloatInput {
                monitoredValue: textureRenderer.center.y
                width: 50
                onNewAcceptableValue: textureRenderer.center.y = value;
            }
            Text {
                font.pixelSize: mystyle.textSize
                text: "height:"
            }
            ScrollableFloatInput {
                monitoredValue: textureRenderer.size.y
                width: 50
                onNewAcceptableValue: textureRenderer.size.y = value;
            }
        }
    ]
}
