import QtQuick 2.2
import NoiseModeler 1.0

SubWindow {
    id: node
    property Module module
    property bool maximized: true
    windowTitle: module.name

    mouseArea.onClicked: {
            maximized = !maximized;
    }

    contents.width: nodeContents.width
    contents.height: nodeContents.height
    contents.children: [
        Row{
            id: nodeContents
            property int minWidth: childrenRect.width// + 2 * horizontalMargins
            property int minHeight: childrenRect.height// + 2 * verticalMargins
            width: childrenRect.width
            height: childrenRect.height

            spacing: 10
            Column{
                Repeater{
                    model: module.inputs
                    NodeInput{model:modelData}
                }
            }

            Column{
                Repeater{
                    model: module.outputs
                    NodeOutput{model:modelData}
                }
            }
        }
    ]
}
