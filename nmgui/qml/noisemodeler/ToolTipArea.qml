import QtQuick 2.0

MouseArea {
    property alias text: toolTip.text
    property alias hideDelay: hideTimer.interval
    property alias showDelay: showTimer.interval
    id: mouseArea
    anchors.fill: parent
    hoverEnabled: true
    Timer {
        id:showTimer
        interval: 1000
        running: (mouseArea.containsMouse && !toolTip.visible)
        onTriggered: toolTip.show();
    }
    Timer {
        id:hideTimer
        interval: 100
        running: !mouseArea.containsMouse && toolTip.visible
        onTriggered: toolTip.hide();
    }
    ToolTip{
        id:toolTip
    }
}
