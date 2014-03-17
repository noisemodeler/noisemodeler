import QtQuick 2.2

SubWindow {
    property variant module
    windowTitle: "Inspector: " + (module ? module.name : "No module")
    contents.children: [
        Text {
            text: "Test"
        }
    ]
}
