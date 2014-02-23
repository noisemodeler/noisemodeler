import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    color: mystyle.graphEditor.bgColor
    property alias contents: contents
    property Graph graph
    MouseArea {
            anchors.fill: parent
            drag.target:contents
            acceptedButtons: Qt.RightButton | Qt.MiddleButton
    }
    Item {
        id:contents
        Repeater {
            id: rep
            model: graph.modules
            Node {
                module: modelData
            }
        }
        TexturePreview{}
    }
    function autoArrangeWindows(){
        contents.x = 0;
        contents.y = 0;
        var curY = 50;
        var curX = 50;
        var maxWidth = 0;
        for(var i=0; i<contents.children.length; ++i){
            var child = contents.children[i];
            if(curY+child.height > graphEditor.height){
                curY = 50;
                curX += maxWidth + 20;
                maxWidth = 0;
            }
            child.y = curY;
            child.x = curX;
            curY += child.height + 50;
            maxWidth = Math.max(maxWidth, child.width);
        }
    }
}
