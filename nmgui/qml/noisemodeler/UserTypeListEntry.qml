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
            height: parent.height
            text: moduleType.name
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/edit.svg'
        }
    }
    ToolTipArea {
        text: moduleType.description
        tip.x: parent.width + 10
        tip.y: parent.height / 2 - tip.height/2
        onDoubleClicked: {
            mockGraph.createModule(modelData);
        }
    }
}
