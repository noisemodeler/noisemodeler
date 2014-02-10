import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    property list<Module> dummyModules
//        Module{
//            Component.onCompleted: {
//                console.log("GRAWRLBOOOOOO!");
//                initjjjjjjjjjjjjjjjj
//            }

//        }
//    ]
//        Module{
//            name:"fBm"
//            inputs:[
//                ModuleInput{name:'octaves'},
//                ModuleInput{name:'gain'},
//                ModuleInput{name:'lacunarity'}
//            ]
//            outputs:[
//                ModuleOutput{name:'out'}
//            ]
//        },
//        Module{
//            name:"add"
//            inputs:[
//                ModuleInput{name:'A'},
//                ModuleInput{name:'B'}
//            ]
//            outputs:[
//                ModuleOutput{name:'out'}
//            ]
//        },
//        Module{
//            name:"sub"
//            inputs:[
//                ModuleInput{name:'lhs'},
//                ModuleInput{name:'rhs'}
//            ]
//            outputs:[
//                ModuleOutput{name:'out'}
//            ]
//        }
//    ]
    anchors.top: parent.top
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.bottom: parent.bottom

    color: mystyle.bgColor

//    Repeater{
//        model:dummyModules
//        Node{module:modelData}
//    }
    Node{module:mockModule}
    Node{module:mockModule2}
    Node{module:mockModule3}
//    TexturePreview{}
}
