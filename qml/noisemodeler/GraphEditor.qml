import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    property list<Module> dummyModules: [
        Module{name:"fbm"},
        Module{name:"Add"},
        Module{name:"Subtract"}
    ]
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.bottom: parent.bottom

    color: mystyle.bgColor

    Node{module:dummyModules[0]}
    Node{module:dummyModules[1]}
    Node{module:dummyModules[2]}
}
