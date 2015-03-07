import QtQuick 2.2

Item {
    id: button
    property alias text: label.text
    property bool active: false
    height: mystyle.topBar.height
    width: label.width + 20 * mystyle.dp
    state: active ? "active" : "inactive"
    states: [
        State {
            name: "inactive"
            PropertyChanges {
                target: highlight
                height: 0
            }
        },
        State {
            name: "active"
            PropertyChanges {
                target: highlight
                height: 5 * mystyle.dp
            }
        }
    ]
    transitions: [
        Transition {
            to: "*"
            NumberAnimation { target: highlight; property: "height"; duration: 200; easing.type: Easing.OutBack; easing.overshoot: 5 }
        }
    ]
    Text {
        anchors.centerIn: parent
        id: label
        color: mystyle.topBar.textColor
        text: "TopBarButton"
        font.pixelSize: mystyle.textSize
        verticalAlignment: Text.AlignVCenter
    }
    Rectangle {
        id: highlight
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: mystyle.topBar.tabHighlightColor
    }
}
