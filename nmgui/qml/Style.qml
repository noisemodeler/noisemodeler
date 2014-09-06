import QtQuick 2.2
QtObject {
    id:style

    //sizes
    property real dp: 1 //device pixel ratio
    property real textSize: 14 * dp
    property real smallTextSize: 10 * dp

    //colors
    property color bgColor: "#444444"
    property color bgColor2: "#525252"
    property color bgColor3: "#666666"
    property color fgColor: "powderBlue"
    property color textColor: "#cccccc"
    property color textOnFgColor: "#000000"
    property color borderColor: "black"
    property color linkStrokeColor: fgColor
    property color toolTipBg: "#AA999999"
    property color checkedColor: "#3333AA"

    property QtObject graphEditor: QtObject {
        property color bgColor: style.bgColor
    }

    property QtObject inspector: QtObject {
        property color bgColor: node.bgColor
        property real width: 200 * dp
    }

    property QtObject moduleTypeBrowser: QtObject {
        property color bgColor: bgColor3
        property real width: 150 * dp
    }

    property QtObject topBar: QtObject {
        property color bgColor: style.bgColor2
        property color textColor: style.textColor
        property color tabHighlightColor: style.fgColor
        property real height: 40 * dp
    }

    property QtObject subWindow: QtObject {
        property color headerColor: style.bgColor
        property color bgColor: node.bgColor
        property real titleHeight: 13 * dp
    }

    property QtObject node: QtObject {
        property color bgColor: Qt.lighter(style.bgColor, 1.8)
    }

    property QtObject connector: QtObject {
        property variant connectedColors: [
            '#88ff88', '#ff8888', '#8888ff',
        ]
        property variant disconnectedColors: [
            Qt.darker(connectedColors[0], 2.8),
            Qt.darker(connectedColors[1], 2.8),
            Qt.darker(connectedColors[2], 2.8)
        ]
        property real height: 20 * dp
    }
    property QtObject textBox: QtObject {
        property color activeBgColor: "white"
        property color inactiveBgColor: "#aaaaaa"
    }
}
