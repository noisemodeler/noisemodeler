import QtQuick 2.2
QtObject {
    id:style
    property int textSize: 20
    property int smallTextSize: 8

    property color bgColor: "#444444"
    property color fgColor: "powderBlue"
    property color textColor: "#cccccc"
    property color textOnFgColor: "#000000"
    property color borderColor: "black"
    property color linkStrokeColor: fgColor
    property color toolTipBg: "#AA999999"

    property QtObject node: QtObject {
        property color bgColor: Qt.lighter(style.bgColor, 1.8)
    }

    property QtObject connector: QtObject {
        property variant connectedColors: [
            '#88ff88', '#ff8888', '#8888ff',
        ]
        property variant disconnectedColors: [
            Qt.darker(connectedColors[0], 1.8),
            Qt.darker(connectedColors[1], 1.8),
            Qt.darker(connectedColors[1], 1.8)
        ]
        property int height: 20
    }
}
