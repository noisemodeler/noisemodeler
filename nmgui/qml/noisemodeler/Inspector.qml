import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Rectangle {
    id: inspector
    color: mystyle.inspector.bgColor

    StackView {
        id: inspectorStack
        delegate: StackViewDelegate{}
    }

    Component {
        id: moduleInspectorComponent
        ModuleInspector {
            z: 50
//            anchors.fill: parent
        }
    }

    function inspectModule(module){
        inspectorStack.pop(null);
        inspectorStack.push({
                                item: moduleInspectorComponent,
                                properties: {
                                    module: module
                                }
                            });
    }
}
