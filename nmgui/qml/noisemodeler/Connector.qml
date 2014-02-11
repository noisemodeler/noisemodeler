import QtQuick 2.2

Rectangle {
    id: connector
    property bool connected: false
    property int dimensionality: 1
    property int tipXdirection: 1
    anchors.verticalCenter: parent.verticalCenter
//    border.color: mystyle.borderColor
    border.width: 0
    height: 8
    width: 8
    color: connected ? mystyle.connector.connectedColors[dimensionality-1] : mystyle.connector.disconnectedColors[dimensionality-1]
    ToolTipArea{
        text: dimensionality+"D signal"
        tip {
            x: if(tipXdirection == 1){connector.width + 10}
               else if(tipXdirection == -1){-10 - tip.width}
               else {0}

            y: connector.height/2 - tip.height/2
        }
    }
}
