import QtQuick 2.2
import QtQuick.Layouts 1.1

SubWindow {
    property variant module
    windowTitle: "Inspector: " + (module ? module.name : "No module")
    contents.children: [
        GridLayout {
//            verticalItemAlignment: Grid.AlignVCenter
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.top: parent.top
            anchors.margins: 6
            columns: 2
//            spacing: 6

            Text {
                text: "rhs:"
            }
            SignalValueEdit {
            }
            Text {
                text: "lhs:"
            }
            SignalValueEdit {
            }
       }
    ]
}
