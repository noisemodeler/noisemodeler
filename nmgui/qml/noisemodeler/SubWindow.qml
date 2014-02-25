import QtQuick 2.2

Rectangle {
    id: subWindow
    width: Math.max(contents.childrenRect.width + borderThickness * 2, nodeLabel.width+3)
    height: contents.childrenRect.height + titleBar.height + borderThickness * 2
    color: mystyle.node.bgColor
//    property int minWidth: Math.max(50, contents.minWidth+borderThickness*2)
//    property int minHeight: contents.minHeight + titleBar.height + borderThickness * 2
    property int titleHeight: 13
    property string windowTitle: "Window Title"
    property alias mouseArea: windowMouseArea
    property alias titleBar: titleBar
    property alias contents: contents
    property int borderThickness: 0
    property bool selected: activeFocus
    SelectionGlow {
        id:selectionGlow
        anchors.fill: parent
        visible: selected
    }

    Rectangle{
        id: titleBar
        anchors.left: subWindow.left
        anchors.right: subWindow.right
        anchors.top: subWindow.top
        height: titleHeight
        color: mystyle.subWindow.bgColor
        Text {
            x: 3
            id: nodeLabel
            text: windowTitle
            font.pointSize: mystyle.smallTextSize
            color: mystyle.textColor
            anchors.verticalCenter: titleBar.Center
        }
    }
    MouseArea{
        id: windowMouseArea
        anchors.fill: subWindow
        drag.target: subWindow
        onPressed: subWindow.focus = true;
//        drag.minimumY: subWindow.titleHeight
//        drag.minimumX: 0
//        drag.maximumX: subWindow.parent.width - subWindow.width
//        drag.maximumY: subWindow.parent.height - subWindow.height
    }
    Item {
        id:contents
        anchors.top: titleBar.bottom
        anchors.left: subWindow.left
        anchors.leftMargin: borderThickness
        anchors.rightMargin: borderThickness
        width: childrenRect.width
        height: childrenRect.height
    }
}
