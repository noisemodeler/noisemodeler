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
        Module{
            name:"Add"
            inputs:[
                ModuleInput{name:'A'},
                ModuleInput{name:'B'}
            ]
        },
        Module{
            name:"Sub"
            inputs:[
                ModuleInput{name:'lhs'},
                ModuleInput{name:'rhs'}
            ]
        }
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
