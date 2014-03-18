import QtQuick 2.2
import QtQuick.Layouts 1.1

RowLayout {
    id: signalValueEdit
    property int fields: 1
    property bool readOnly: false

//    spacing: 6
    Repeater {
        id:repeater
        model: fields

        LineInput {
            Layout.fillWidth: true
            readOnly: signalValueEdit.readOnly
            validator: DoubleValidator{}
        }
    }
}
