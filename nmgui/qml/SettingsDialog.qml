import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1

Window {
    function open() {
        visible = true;
    }
    color:  mystyle.bgColor
    width: 400 * mystyle.dp
    height: 400 * mystyle.dp
    Item {
        anchors.fill: parent
        anchors.margins: 5 * mystyle.dp
        ColumnLayout {
            anchors.fill: parent
            RowLayout {
                Text {
                    text: "User interface scale: "
                    font.pixelSize: 14 * mystyle.dp
                }
                LineInput {
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignRight
                    validator: DoubleValidator {
                        bottom: 0.1
                        top: 10
                    }
                    onNewAcceptableValue: {
                        mystyle.dp = parseFloat(newText);
                    }
                }
            }
        }
    }
}
