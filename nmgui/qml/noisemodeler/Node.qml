import QtQuick 2.2
import NoiseModeler 1.0

SubWindow {
    id: node
    property Module module
    windowTitle: module.name
    visible: module

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
    function deleteNode(){
        if(!module.moduleType.removable)return;
        graph.removeModule(node.module);
    }

    Keys.onPressed: {
        if(event.key === Qt.Key_Delete || event.key === Qt.Key_Backspace){
            deleteNode();
        }
    }
}
