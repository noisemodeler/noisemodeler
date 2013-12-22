import QtQuick 2.2

Rectangle {
    id:graphEditor
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.bottom: parent.bottom

    Node{nodeName: "Add"}
    Node{nodeName: "Subtract"}
    Node{}
}
