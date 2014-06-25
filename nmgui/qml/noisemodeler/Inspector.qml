import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

SubWindow {
    id: inspector
    color: mystyle.inspector.bgColor

    StackView {
        id: inspectorStack
        delegate: StackViewDelegate{}
        width: inspector.width
        height: inspector.height - inspector.titleHeight
    }

    Component {
        id: moduleInspectorComponent
        ModuleInspector {
            z: 50
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
