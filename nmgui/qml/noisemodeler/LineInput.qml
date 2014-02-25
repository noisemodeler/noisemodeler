import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    property alias text: input.text
    property alias maximumLength: input.maximumLength
    property alias inputMask: input.inputMask
    property alias validator: input.validator
    property alias acceptableInput: input.acceptableInput
    signal newAcceptableValue(string newText)
    width: 50; height: 18
    TextInput {
        id: input
        color: "black"
        font.pixelSize: 12; font.bold: true
        anchors.centerIn: parent
        width: parent.width-4
        focus: true
        clip: true
        onEditingFinished: notifyIfChangedAndAcceptable()
        Keys.onReleased: notifyIfChangedAndAcceptable()
        property string lastAcceptableString: ""
        function notifyIfChangedAndAcceptable(){
            if(!acceptableInput)return;
            if(text===lastAcceptableString)return;
            lastAcceptableString = text;
            newAcceptableValue(text);
        }
    }
}
