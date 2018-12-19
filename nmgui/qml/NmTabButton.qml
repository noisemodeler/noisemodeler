import QtQuick 2.2
import QtQuick.Controls 2.1

TabButton {
    id: button
    property bool active: false
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
    contentItem: Text {
        id: label
        color: mystyle.topBar.textColor
        text: button.text
        font.pixelSize: mystyle.textSize
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
    background: Item {
        implicitWidth: label.width + 80 * mystyle.dp
        Rectangle {
            id: highlight
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: mystyle.topBar.tabHighlightColor
        }
    }
}
