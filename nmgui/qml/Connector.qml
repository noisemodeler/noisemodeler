import QtQuick 2.2

Rectangle {
    id: connector
    property bool connected: false
    property int dimensionality: 1
    property int tipXdirection: 1
    property color connectedColor: mystyle.connector.connectedColors[dimensionality-1]
    property color disconnectedColor: mystyle.connector.disconnectedColors[dimensionality-1]
    anchors.verticalCenter: parent.verticalCenter
//    border.color: mystyle.borderColor
    border.width: 0
    height: 8 * mystyle.dp
    width: 8 * mystyle.dp
    color: connected ? connectedColor : disconnectedColor
    ToolTipArea{
        text: dimensionality+"D signal"
        tip {
            x: if(tipXdirection == 1){connector.width + 10 * mystyle.dp}
               else if(tipXdirection == -1){-10 * mystyle.dp - tip.width}
               else {0}

            y: connector.height/2 - tip.height/2
        }
    }
}
