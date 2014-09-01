import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

Rectangle {
    id: inspector
    color: mystyle.inspector.bgColor
    property string windowTitle: "inspector"
    property real titleHeight: mystyle.subWindow.titleHeight

    Rectangle{
        id: titleBar
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: titleHeight
        color: mystyle.subWindow.headerColor
        Text {
            id: nodeLabel
            x: 3
            width: parent.width-3
            elide: Text.ElideRight
            anchors.verticalCenter: titleBar.Center
            text: windowTitle
            font.pixelSize: mystyle.smallTextSize
            color: mystyle.textColor
        }
    }

    StackView {
        id: inspectorStack
        delegate: StackViewDelegate{}
        anchors.top: titleBar.bottom
        width: inspector.width
        height: inspector.height - inspector.titleHeight
    }

    Component {
        id: moduleInspectorComponent
        ModuleInspector {
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
        windowTitle = "inspecting module: " + module.name;
    }

    Component {
        id: moduleTypeInspectorComponent
        ModuleTypeInspector {
            id: moduleTypeInspector
        }
    }

    function inspectModuleType(moduleType){
        inspectorStack.pop(null);
        inspectorStack.push({
                                item: moduleTypeInspectorComponent,
                                properties: {
                                    moduleType: moduleType
                                }
                            });
        windowTitle = "inspecting type: " + moduleType.name;
    }
}
