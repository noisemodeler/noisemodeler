import QtQuick 2.2
import QtQuick.Layouts 1.1

SubWindow {
    property variant module
    windowTitle: "Inspector: " + (module ? module.name : "No module")
    contents.children: [
        ColumnLayout {
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.top: parent.top
            anchors.margins: 6

            Repeater{
                model: module.inputs
                RowLayout{
                    Text {
                        text: modelData.name + ":"
                        Layout.maximumWidth: 40
                        Layout.minimumWidth: 40
                        elide: Text.ElideRight
                    }
                    SignalValueEdit {
                    }
                }
            }
        }
    ]
}
