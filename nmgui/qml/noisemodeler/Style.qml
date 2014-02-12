import QtQuick 2.2
QtObject {
    id:style

    property color molokaiwhite         : "#ffffff"
    property color molokaifg            : "#f8f8f0"
    property color molokaired           : "#ff0000"
    property color molokaipink          : "#f92672"
    property color molokaiorangeplus5   : "#ef5939"
    property color molokaiorange        : "#fd971f"
    property color molokaiyellow        : "#ffff00"
    property color molokaidarkgoldenrod : "#e6db74"
    property color molokaiwheat         : "#c4be89"
    property color molokaiolive         : "#808000"
    property color molokaichartreuse    : "#a6e22e"
    property color molokailime          : "#00ff00"
    property color molokaigreen         : "#008000"
    property color molokaidarkwine      : "#1e0010"
    property color molokaimaroon        : "#800000"
    property color molokaiwine          : "#960050"
    property color molokaiteal          : "#008080"
    property color molokaiaqua          : "#00ffff"
    property color molokaiblue          : "#66d9ef"
    property color molokaislateblue     : "#7070f0"
    property color molokaipurple        : "#ae81ff"
    property color molokaipalevioletred : "#d33682"
    property color molokaigreyminus2    : "#bcbcbc"
    property color molokaigreyminus1    : "#8f8f8f"
    property color molokaigrey          : "#808080"
    property color molokaigreyplus2     : "#403d3d"
    property color molokaigreyplus3     : "#4c4745"
    property color molokaigreyplus5     : "#232526"
    property color molokaibg            : "#1b1d1e"
    property color molokaigreyplus10    : "#080808"
    property color molokaidark          : "#000000"
    property color molokaibase01        : "#465457"
    property color molokaibase02        : "#455354"
    property color molokaibase03        : "#293739"
    property color molokaidodgerblue    : "#13354a"

    property int textSize: 20
    property int smallTextSize: 8

    property color bgColor: "#444444"
    property color bgColor2: "#525252"
    property color fgColor: "powderBlue"
    property color textColor: "#cccccc"
    property color textOnFgColor: "#000000"
    property color borderColor: "black"
    property color linkStrokeColor: fgColor
    property color toolTipBg: "#AA999999"

    property QtObject graphEditor: QtObject {
        property color bgColor: style.bgColor
    }

    property QtObject topBar: QtObject {
        property color bgColor: style.bgColor2
        property color textColor: style.textColor
    }

    property QtObject subWindow: QtObject {
        property color bgColor: style.bgColor
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
            Qt.darker(connectedColors[1], 2.8)
        ]
        property int height: 20
    }
}
