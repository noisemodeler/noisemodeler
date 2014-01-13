import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    property list<Module> dummyModules: [
        Module{
            name:"fBm"
            inputs:[
                ModuleInput{name:'octaves'},
                ModuleInput{name:'gain'},
                ModuleInput{name:'lacunarity'}
            ]
        },
        Module{name:"Add"},
        Module{name:"Subtract"}
    ]
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.bottom: parent.bottom

    color: mystyle.bgColor

    Repeater{
        model:dummyModules
        Node{module:modelData}
    }
}
