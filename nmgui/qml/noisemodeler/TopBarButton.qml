import QtQuick 2.0

Item {
    id: button
    signal clicked
    property alias text: label.text
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: label.width + 20
    state: "inactive"
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
                height: 5
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
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
    }
    Rectangle {
        id: highlight
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "powderblue"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if(button.state=="active"){
                button.state = "inactive";
            } else {
                button.state = "active";
            }
        }
    }
}
