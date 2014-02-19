import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    color: mystyle.graphEditor.bgColor
    property alias contents: contents
    MouseArea {
            anchors.fill: parent
            onClicked: console.log("kerbewn")
            drag.target:contents
    }
    Item {
        id:contents
    }
}
