import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

Window {
    property string version: core.versionString
    function open(){
        visible = true;
    }

    color: mystyle.bgColor
    id: aboutDialog
    width: 520 * mystyle.dp
    height: 390 * mystyle.dp
    modality: Qt.WindowModal
    flags: Qt.Dialog | Qt.WindowCloseButtonHint | Qt.CustomizeWindowHint | Qt.WindowTitleHint
    title: "About Noise Modeler"

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        Rectangle {
            color: mystyle.inspector.bgColor
            Layout.fillWidth: true
            implicitHeight: aboutText.implicitHeight + 8 * mystyle.dp
            implicitWidth: aboutText.implicitWidth
            Text {
                anchors.centerIn: parent
                id: aboutText
                width: parent.width - 8 * mystyle.dp
                wrapMode: Text.WordWrap
                text: "Noise Modeler "+version+"\nCopyright (c) 2014 Johan Klokkhammer Helsing (johanhelsing@gmail.com)"
                font.pixelSize: mystyle.textSize
                font.bold: true
            }
        }

        ScrollView {
            id: scrollView
            Layout.fillHeight: true
            Layout.fillWidth: true
            Rectangle {
                Text {
                    id: licenseText
                    anchors.fill: parent
                    wrapMode: Text.WordWrap
                    text: core.licenseText
                    font.family: "monospace"
                    font.pixelSize: mystyle.smallTextSize
                }
            }
        }

        Rectangle {
            id: nmButton
            color: mystyle.inspector.bgColor
            implicitWidth: buttonText.implicitWidth + 12 * mystyle.dp
            implicitHeight: buttonText.implicitHeight + 8 * mystyle.dp
            Layout.fillWidth: true
            Text {
                id: buttonText
                anchors.centerIn: parent
                text: "close"
                color: "black"
                font.pixelSize: mystyle.textSize
            }
            MouseArea {
                anchors.fill: parent
                onClicked: aboutDialog.close();
            }
        }
    }
}
