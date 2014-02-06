import QtQuick 2.0

Rectangle {
    id: subWindow
    x: parent.width/2
    y: parent.height/2
    width: contents.childrenRect.width + borderThickness * 2
    height: contents.childrenRect.height + borderThickness * 2
    color: mystyle.node.bgColor
    property int minWidth: Math.max(50, contents.minWidth+borderThickness*2)
    property int minHeight: contents.minHeight + borderThickness * 2
    property int titleHeight: 13
    property string windowTitle: "Window Title"
    property alias mouseArea: windowMouseArea
    property alias titleBar: titleBar
    property alias contents: contents
    property int borderThickness: 0

//    border.color: mystyle.borderColor

    Rectangle{
        id: titleBar
        anchors.left: subWindow.left
        anchors.right: subWindow.right
        anchors.bottom: subWindow.top
        height: titleHeight
//        border.width: 0
//        border.color: mystyle.borderColor
        color: mystyle.bgColor
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
        anchors.topMargin: -titleHeight
        drag.target: subWindow

        drag.minimumY: subWindow.titleHeight
        drag.minimumX: 0
        drag.maximumX: subWindow.parent.width - subWindow.width
        drag.maximumY: subWindow.parent.height - subWindow.height
    }
    Item {
        id:contents
        anchors.top: subWindow.top
        anchors.left: subWindow.left
        anchors.leftMargin: borderThickness
        anchors.rightMargin: borderThickness
        width: childrenRect.width
        height: childrenRect.height
    }
}
