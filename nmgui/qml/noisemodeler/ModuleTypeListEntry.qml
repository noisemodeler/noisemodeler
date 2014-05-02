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
    anchors.left: parent ? parent.left : undefined //TODO this is weird, parent is undefined when loading new documents
    anchors.right: parent ? parent.right : undefined
    RowLayout {
        height: parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true
            elide: Text.ElideRight
            height: parent.height
            text: moduleType.name
            verticalAlignment: Text.AlignVCenter
        }
        ToolBarIcon {
            onClicked: editClicked()
            source: 'qrc:///icons/edit.svg'
            visible: !moduleType.builtin
            Layout.alignment: Qt.AlignRight
        }
        ToolBarIcon {
            onClicked: addClicked()
            source: 'qrc:///icons/add.svg'
            Layout.alignment: Qt.AlignRight
        }
    }
    ToolTipArea {
        text: moduleType.description
        tip.y: parent.height
        tip.width: parent.width
    }
}
