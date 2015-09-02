import QtQuick 2.2

Image {
    signal clicked
    property bool enabled: true
    property alias toolTipText: toolTipArea.text

    width: 16 * mystyle.dp
    height: width
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
