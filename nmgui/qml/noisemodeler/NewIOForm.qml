import QtQuick 2.2
import QtQuick.Layouts 1.1

RowLayout {
    id: newIOForm
    visible: !moduleType.builtin
    property bool acceptableInput: dimensionalityInput.acceptableInput && nameInput.acceptableInput
    signal addClicked(int dimensionality, string name)
    LineInput {
        id: dimensionalityInput
        Layout.maximumWidth: 18
        validator: IntValidator{bottom: 1; top: 4;}
        horizontalAlignment: Qt.AlignHCenter
    }
    LineInput {
        id: nameInput
        Layout.fillWidth: true
        validator: RegExpValidator { regExp: /[^ ]+/ }
    }
    ToolBarIcon {
        enabled: parent.acceptableInput
        onClicked: {
            addClicked(parseInt(dimensionalityInput.text), nameInput.text);
        }
        source: 'qrc:///icons/add.svg'
        Layout.alignment: Qt.AlignRight
    }
}
