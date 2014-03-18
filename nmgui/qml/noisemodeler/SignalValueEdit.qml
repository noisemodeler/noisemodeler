import QtQuick 2.2
import QtQuick.Layouts 1.1

RowLayout {
    id: signalValueEdit
//    spacing: 6
    Repeater {
        id:repeater
        model: 3

        LineInput {
            Layout.fillWidth: true
        }
    }
}
