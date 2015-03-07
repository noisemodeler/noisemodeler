import QtQuick 2.2

MouseArea {
    property alias text: tip.text
    property alias tip: tip
    property alias hideDelay: hideTimer.interval
    property alias showDelay: showTimer.interval
    id: mouseArea
    anchors.fill: parent
    hoverEnabled: true
    acceptedButtons: Qt.NoButton
    Timer {
        id: showTimer
        interval: 1000
        running: (mouseArea.containsMouse && !tip.visible)
        onTriggered: tip.show();
    }
    Timer {
        id: hideTimer
        interval: 100
        running: !mouseArea.containsMouse && tip.visible
        onTriggered: tip.hide();
    }
    ToolTip{
        id:tip
    }
}
