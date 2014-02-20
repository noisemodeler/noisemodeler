import QtQuick 2.0
import NoiseModeler 1.0

Rectangle {
    property alias text: input.text
    property alias maximumLength: input.maximumLength
    width: 50; height: 18
    TextInput {
        id: input
        color: "black"
        font.pixelSize: 12; font.bold: true
        anchors.centerIn: parent
        width: parent.width-4
        focus: true
        clip: true
    }
}
