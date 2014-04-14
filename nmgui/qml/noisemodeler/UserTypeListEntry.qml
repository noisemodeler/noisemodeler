import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Item{
    id: moduleTypeListEntry
    property var moduleType
    signal editClicked()
    signal addClicked()
    height: 30
    anchors.left: parent.left
    anchors.right: parent.right
    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        Text {
            Layout.fillWidth: true
            elide: Text.ElideRight
            height: parent.height
            text: moduleType.name
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            MouseArea{
                anchors.fill: parent
                onClicked: editClicked()
            }
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/edit.svg'
        }
        Image {
            MouseArea{
                anchors.fill: parent
                onClicked: addClicked()
            }
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/add.svg'
        }
    }
    ToolTipArea {
        text: moduleType.description
        tip.y: parent.height
        tip.width: parent.width
    }
}
