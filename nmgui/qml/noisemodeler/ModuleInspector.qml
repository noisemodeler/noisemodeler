import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: moduleInspector
    property variant module
    property string windowTitle: "inspector: " + (module ? module.name : "no module")
    color: mystyle.inspector.bgColor

    //I would use module.inputs directly, but for some reason
    //that doesn't work. So we're using this hack
    property variant inputs
    onModuleChanged: { inputs = module===undefined ? undefined : module.inputs; }

    ColumnLayout {
        //            visible: module ? true : false
        opacity: module ? 100 : 0 //for weird resons, it crashes with visible, but opacity is fine

        //            anchors.left:parent.left
        //            anchors.right:parent.right
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 6
        width: moduleInspector.width - anchors.margins * 2

        RowLayout {
            InspectorLabel {
                text: "name:"
            }
            LineInput {
                Layout.fillWidth: true
                text: module ? module.name : "error"
                onTextChanged: if(module)module.name = text;
            }
        }

        RowLayout {
            InspectorLabel {
                text: "type:"
            }
            LineInput {
                Layout.fillWidth: true
                readOnly: true
                text: module ? module.moduleType.name : "error"
            }
        }
        RowLayout {
            InspectorLabel {
                text: ""
            }
            Text {
                Layout.fillWidth: true
                text: module ? module.moduleType.description : "error"
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }

        ColumnLayout {
            Repeater{
                //I would use module.inputs directly, but for some reason
                //that doesn't work.
                model: inputs

                RowLayout{
                    InspectorLabel {
                        text: modelData.name + ":"
                    }
                    SignalValueEdit {
                        id: signalValueEdit
                        fields: modelData.dimensionality
                        readOnly: modelData.outputLink !== null
                        onValueChanged: {
                            var vector = Qt.vector4d(values[0], values[1], values[2], values[3]);
                            modelData.unlinkedValue = vector;
                        }
                        Component.onCompleted: updateValue(modelData.unlinkedValue)
                        Connections {
                            target: modelData
                            onUnlinkedValueChanged: signalValueEdit.updateValue(modelData.unlinkedValue)
                        }
                    }
                }
            }
        }

        RowLayout {
            Text {
                text: "comments:"
                Layout.fillWidth: true
            }
        }
        RowLayout {
            Rectangle {
                Layout.fillWidth: true
                height: Math.max(12+6, commentEdit.contentHeight+6)
                TextEdit {
                    id: commentEdit
                    anchors.fill: parent
                    anchors.margins: 3
                    text: module ? module.description : "error"
                    wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
                    onTextChanged: if(module)module.description = text;
                }
            }
        }

    }
}
