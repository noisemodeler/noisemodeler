import QtQuick 2.2

Rectangle {
    color: mystyle.topBar.bgColor
    height: 40
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    Row{
        anchors.fill: parent
        TabButton {
            text: "Menu"
        }
//        spacing: 95
//        Item {
//            anchors.bottom: parent.bottom
//            anchors.top:parent.top
////            height: 20
//            width: text.width + 20
//            Text{
//                x:10
//                anchors.top: parent.top
//                anchors.bottom: parent.bottom
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//                id: text
//                font.pixelSize: 14
//                text: "Height"
//            }
//            Rectangle {
//                color: mystyle.graphEditor.bgColor
//                anchors.bottom: parent.bottom
//                height: parent.height - 3
//                anchors.right: parent.right
//                anchors.left: parent.left
//                z: -100
//            }
//        }

    }
}
