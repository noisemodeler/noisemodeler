import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Image {
    property bool enabled: true
    signal clicked
    property alias toolTipText: toolTipArea.text
    opacity: enabled ? 1 : 0.5
    MouseArea {
        anchors.fill: parent
        onClicked: if(parent.enabled)parent.clicked()
    }
    source: 'qrc:///icons/edit.svg'
    ToolTipArea {
        id: toolTipArea
        text: ""
        visible: text !== ""
        tip.x: parent.width + 5
        tip.y: parent.height / 2 - height/2
    }
}
