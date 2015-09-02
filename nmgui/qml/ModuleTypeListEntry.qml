import QtQuick 2.2
import QtQuick.Layouts 1.1

Item{
    id: moduleTypeListEntry
    property var moduleType
    signal editClicked()
    signal addClicked()
    signal inspectClicked()
    height: 30 * mystyle.dp
    anchors.left: parent ? parent.left : undefined //TODO this is weird, parent is undefined when loading new documents
    anchors.right: parent ? parent.right : undefined
    RowLayout {
        height: parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10 * mystyle.dp
        anchors.rightMargin: 10 * mystyle.dp
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.fill: parent
                id: text
                elide: Text.ElideRight
                height: parent.height
                text: moduleType.name
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: mystyle.textSize
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    inspectClicked();
                }
            }
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
