import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    property alias text: input.text
    property alias maximumLength: input.maximumLength
    property alias inputMask: input.inputMask
    property alias validator: input.validator
    property alias acceptableInput: input.acceptableInput
    property alias textInput: input
    property alias readOnly: input.readOnly
    property alias horizontalAlignment: input.horizontalAlignment
    signal newAcceptableValue(string newText)
    implicitWidth: 60 * mystyle.dp
    height: 18 * mystyle.dp
    color: readOnly ? mystyle.textBox.inactiveBgColor : mystyle.textBox.activeBgColor
    TextInput {
        id: input
        color: "black"
        font.pixelSize: 12 * mystyle.dp
        font.bold: true
        anchors.centerIn: parent
        width: parent.width-4
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
        //this makes the start of the input visible if the box is too small
        onTextChanged: if(!focus)cursorPosition = 0;
    }
}
