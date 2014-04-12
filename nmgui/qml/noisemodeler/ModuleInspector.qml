import QtQuick 2.2
import QtQuick.Layouts 1.1

SubWindow {
    property variant module
    windowTitle: "inspector: " + (module ? module.name : "no module")
    contents.children: [
        ColumnLayout {
            visible: module ? true : false
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.top: parent.top
            anchors.margins: 6

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
                    model: module ? module.inputs : 0
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
    ]
}
