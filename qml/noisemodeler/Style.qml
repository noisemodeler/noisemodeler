import QtQuick 2.2
QtObject {
    id:style
    property int textSize: 20

    property color bgColor: "#444444"
    property color fgColor: "powderBlue"
    property color textColor: "#cccccc"
    property color textOnFgColor: "#000000"
    property color borderColor: "black"

    property QtObject node: QtObject {
        property color bgColor: Qt.lighter(style.bgColor, 1.5)
        property color connectorColor: '#88FF88'
    }
}
