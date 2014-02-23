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
                anchors.fill: parent
                text: modelData.name
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onPressed: {
                    row.ListView.view.currentIndex = index;
                }
                onDoubleClicked: {
                    console.log("add new module to graph");
                    console.log(modelData);
                    mockGraph.createModule(modelData, "testModule");
//                    ModuleType a = ModuleType();
                }
            }
        }
    }
    ListView {
        anchors.fill: parent
        model: [ addModuleType, demuxModuleType ]
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
