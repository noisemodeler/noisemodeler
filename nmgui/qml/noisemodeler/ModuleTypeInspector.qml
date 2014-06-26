import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: moduleTypeInspector
    property variant moduleType: moduleType
    color: mystyle.inspector.bgColor
    ColumnLayout {
        anchors.margins: 6
        anchors.fill: parent
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
        RowLayout {
            Text {
                text: "description:"
            }
        }
        RowLayout {
            Rectangle {
                color: moduleType.builtin ? mystyle.textBox.inactiveBgColor : mystyle.textBox.activeBgColor
                Layout.fillWidth: true
                height: Math.max(12+6, commentEdit.contentHeight+6)
                TextEdit {
                    id: commentEdit
                    anchors.fill: parent
                    anchors.margins: 3
                    readOnly: moduleType.builtin
                    text: moduleType.description
                    wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
                    onTextChanged: if(moduleType && !moduleType.builtin)moduleType.description = text;
                }
            }
        }
        Item{Layout.fillHeight: true}
    }
}
