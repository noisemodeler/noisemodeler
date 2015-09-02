import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    color: mystyle.topBar.bgColor
    height: mystyle.topBar.height
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    RowLayout {
        spacing: 15 * mystyle.dp
        anchors.fill: parent
        Item {
            width: 1 * mystyle.dp
        }
        ToolBarIcon {
            source: 'qrc:///icons/save.svg'
            onClicked: saveDialog.open();
            toolTipText: "Save"
        }
        ToolBarIcon {
            source: 'qrc:///icons/open.svg'
            onClicked: openDialog.open();
            toolTipText: "Open"
        }
        Item {
            Layout.fillWidth: true
        }
        ToolBarIcon {
            source: 'qrc:///icons/settings.svg'
            onClicked: settingsDialog.open();
            toolTipText: "Settings"
        }
        ToolBarIcon {
            source: 'qrc:///icons/about.svg'
            onClicked: aboutDialog.open();
            toolTipText: "About Noise Modeler"
        }
        Item {
            width: 5 * mystyle.dp
        }
    }
}
