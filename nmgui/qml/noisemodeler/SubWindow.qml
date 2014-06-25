import QtQuick 2.2
import QtQuick.Layouts 1.1

Rectangle {
    id: subWindow
    implicitWidth: contents.implicitWidth
    implicitHeight: contents.implicitHeight + titleBar.height
    color: mystyle.subWindow.bgColor
    default property alias contentsData: contents.data
    property int titleHeight: 13
    property string windowTitle: "Window Title"
    property alias mouseArea: windowMouseArea
    property alias titleBar: titleBar
    property alias contents: contents
    property bool selected: focus
    property bool resizeContents: false
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
        color: mystyle.subWindow.headerColor
        Text {
            id: nodeLabel
            x: 3
            width: parent.width-3
            elide: Text.ElideRight
            anchors.verticalCenter: titleBar.Center
            text: windowTitle
            font.pointSize: mystyle.smallTextSize
            color: mystyle.textColor
        }
    }
    MouseArea{
        id: windowMouseArea
        anchors.fill: subWindow
        drag.target: subWindow
        onPressed: {
//            subWindow.focus = true;
            subWindow.forceActiveFocus();
        }
    }
    Item {
        id: contents
        anchors.top: titleBar.bottom
        anchors.left: subWindow.left
        width: resizeContents ? subWindow.width : undefined
        height: resizeContents ? subWindow.height : undefined
        implicitWidth: childrenRect.width
        implicitHeight: childrenRect.height
    }
}
