import QtQuick 2.2

SubWindow {
    property variant module
    windowTitle: "Inspector: " + (module ? module.name : "No module")
    contents.children: [
        Grid {
            verticalItemAlignment: Grid.AlignVCenter
            anchors.fill:parent
            anchors.margins: 6
            columns: 2
            spacing: 6

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
