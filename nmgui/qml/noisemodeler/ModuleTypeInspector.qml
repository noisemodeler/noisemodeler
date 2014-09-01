import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: moduleTypeInspector
    property variant moduleType: moduleType
    color: mystyle.inspector.bgColor
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6 * mystyle.dp
        RowLayout {
            InspectorLabel {
                text: "name:"
            }
            LineInput {
                readOnly: moduleType.builtin
                text: moduleType.name
                Layout.fillWidth: true
                onTextChanged: {
                    //TODO: additional sanity tests
                    if(moduleType){
                        moduleType.name = text;
                    }
                }
            }
        }
        Text {
            text: "inputs:"
            font.pixelSize: mystyle.textSize
        }
        ColumnLayout {
            Repeater {
                model: moduleType.inputs
                ModuleTypeInspectorIOEntry {
                    onRemoveClicked:  {
                        moduleType.removeInput(modelData);
                    }
                }
            }
            Item{width:1} //leave this here because layouts get messed
                          //up if sub-layouts have no children
        }
        NewIOForm {
            onAddClicked: {
                moduleType.addInput(name, dimensionality);
            }
        }

        Text {
            text: "outputs:"
            font.pixelSize: mystyle.textSize
        }
        ColumnLayout {
             Repeater {
                model: moduleType.outputs
                ModuleTypeInspectorIOEntry {
                    onRemoveClicked:  {
                        moduleType.removeOutput(modelData);
                    }
                }
            }
            Item{width:1} //leave this here because layouts get messed
                          //up if sub-layouts have no children
        }
        NewIOForm {
            onAddClicked: {
                moduleType.addOutput(name, dimensionality);
            }
        }

        RowLayout {
            Text {
                text: "description:"
                font.pixelSize: mystyle.textSize
            }
        }
        RowLayout {
            Rectangle {
                color: moduleType.builtin ? mystyle.textBox.inactiveBgColor : mystyle.textBox.activeBgColor
                Layout.fillWidth: true
                height: Math.max((12+6)*mystyle.dp, commentEdit.contentHeight+6*mystyle.dp)
                TextEdit {
                    id: commentEdit
                    anchors.fill: parent
                    anchors.margins: 3 * mystyle.dp
                    readOnly: moduleType.builtin
                    text: moduleType.description
                    wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
                    onTextChanged: if(moduleType && !moduleType.builtin)moduleType.description = text;
                    font.pixelSize: mystyle.textSize
                }
            }
        }

        Item{Layout.fillHeight: true}
    }
}
