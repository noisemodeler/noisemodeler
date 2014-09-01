import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.1

Rectangle {
    color: mystyle.topBar.bgColor
    id: topBar
    height: mystyle.topBar.height
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    RowLayout {
        anchors.fill: parent
        Item{
            width: 5 * mystyle.dp
        }
        ToolBarIcon{
            Layout.alignment: Qt.AlignLeft
            source: 'qrc:///icons/save.svg'
            onClicked: saveDialog.open();
            toolTipText: "Save"
        }
        ToolBarIcon{
            Layout.alignment: Qt.AlignLeft
            source: 'qrc:///icons/open.svg'
            onClicked: openDialog.open();
            toolTipText: "Open"
        }
        Item {
            Layout.fillWidth: true
        }
        ToolBarIcon{
            Layout.alignment: Qt.AlignRight
            source: 'qrc:///icons/about.svg'
            onClicked: aboutDialog.open();
            toolTipText: "About Noise Modeler"
        }
        Item{
            width: 5 * mystyle.dp
        }
    }
}
