import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Image {
    width: 16 * mystyle.dp
    height: 16 * mystyle.dp
    property bool enabled: true
    signal clicked
    property alias toolTipText: toolTipArea.text
    opacity: enabled ? 1 : 0.5
    source: 'qrc:///icons/edit.svg'
    sourceSize.width: width
    sourceSize.height: height
    MouseArea {
        anchors.fill: parent
        onClicked: if(parent.enabled)parent.clicked()
    }
    ToolTipArea {
        id: toolTipArea
        text: ""
        visible: text !== ""
        tip.x: parent.width + 5 * mystyle.dp
        tip.y: parent.height / 2 - height/2
    }
}
