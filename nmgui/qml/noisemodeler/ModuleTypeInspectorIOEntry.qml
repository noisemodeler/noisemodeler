import QtQuick 2.2
import QtQuick.Layouts 1.1

RowLayout {
    id: moduleTypeInspectorIOEntry
    signal removeClicked()
    Rectangle {
        height: 18
        width: height
        color: mystyle.connector.connectedColors[modelData.dimensionality-1]
        Text {
            font.pixelSize: 12
            font.bold: true
            text: modelData.dimensionality
            anchors.centerIn: parent
        }
    }
    Text {
        text: modelData.name
        Layout.fillWidth: true
    }
    ToolBarIcon {
        visible: !moduleType.builtin
        onClicked: removeClicked()
        source: 'qrc:///icons/delete.svg'
        Layout.alignment: Qt.AlignRight
    }
}
