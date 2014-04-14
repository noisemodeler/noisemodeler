import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Item{
    height: 30
    anchors.left: parent.left
    anchors.right: parent.right
    property var moduleType
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
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/edit.svg'
        }
        Image {
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/add.svg'
        }
    }
    ToolTipArea {
        text: moduleType.description
        tip.y: parent.height
        tip.width: parent.width
        onDoubleClicked: {
            mockGraph.createModule(modelData);
        }
    }
}
