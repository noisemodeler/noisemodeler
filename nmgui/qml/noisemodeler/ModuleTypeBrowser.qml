import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id: moduleTypeBrowser
    color:"#666666"
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.top: menu.bottom
    width:150
    Component {
        id: moduleTypeEntry
        Item {
            id:row
            height:30
            anchors.left: parent.left
            anchors.right: parent.right
            Text {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                x: 10
                text: modelData.name
                verticalAlignment: Text.AlignVCenter
            }
            ToolTipArea {
                text: modelData.description
                tip.x: parent.width + 10
                tip.y: parent.height / 2 - tip.height/2
                onPressed: {
                    row.ListView.view.currentIndex = index;
                }
                onDoubleClicked: {
                    mockGraph.createModule(modelData);
                }
            }
        }
    }
    ListView {
        anchors.fill: parent
        model: typeManager.builtinTypes
        delegate: moduleTypeEntry
        highlightMoveDuration: 0
        highlight: Rectangle {
            color: "lightsteelblue"
            anchors.left: parent.left
            anchors.right: parent.right
        }
        focus: true
    }
}
