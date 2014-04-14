import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Rectangle {
    id: moduleTypeBrowser
    color: mystyle.moduleTypeBrowser.bgColor
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    anchors.top: menu.bottom
    width: 150

    ScrollView {
        id: scrollView
        anchors.fill: parent
        style: ScrollViewStyle{
            scrollBarBackground: Item{}
            transientScrollBars: true
        }
        Column {
            width: scrollView.width
            Item {
                height: 30
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    text: "user types:"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    x: 10
                }
            }
            Repeater {
                model: typeManager.userTypes
                ModuleTypeListEntry {
                    moduleType: modelData
                    onAddClicked: console.log("Add user type to graph")
                    onEditClicked: console.log("edit user type")
                }
            }

            Item {
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    height: 30
                    anchors.bottom: parent.bottom
                    text: "built-in types:"
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    x: 10
                }
            }

            Repeater{
                model: typeManager.builtinTypes
                ModuleTypeListEntry {
                    moduleType: modelData
                }
            }
        }
    }
    //    ListView {
    //        anchors.fill: parent
                //        model: typeManager.builtinTypes
                //        delegate: moduleTypeEntry
                //        highlightMoveDuration: 0
                //        highlight: Rectangle {
                //            color: "lightsteelblue"
//            anchors.left: parent.left
//            anchors.right: parent.right
//        }
//        focus: true
//    }
}
