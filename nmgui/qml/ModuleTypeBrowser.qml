import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import NoiseModeler 1.0

Rectangle {
    id: moduleTypeBrowser
    signal addModuleClicked(ModuleType moduleType)
    signal editModuleTypeClicked(ModuleType moduleType)
    signal inspectModuleTypeClicked(ModuleType moduleType)
    color: mystyle.moduleTypeBrowser.bgColor
    width: mystyle.moduleTypeBrowser.width

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
                height: 30 * mystyle.dp
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    text: "user types:"
                    font.bold: true
                    font.pixelSize: mystyle.textSize
                    verticalAlignment: Text.AlignVCenter
                    x: 10 * mystyle.dp
                }
                ToolBarIcon {
                    source: "qrc:///icons/add.svg"
                    onClicked: document.typeManager.createUserType();
                    anchors.right: parent.right
                    anchors.rightMargin: 10 * mystyle.dp
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Repeater {
                model: document.typeManager.userTypes
                ModuleTypeListEntry {
                    moduleType: modelData
                    onAddClicked: addModuleClicked(moduleType)
                    onEditClicked: editModuleTypeClicked(moduleType)
                    onInspectClicked: inspectModuleTypeClicked(moduleType)
                }
            }

            Item {
                height: 40 * mystyle.dp
                anchors.left: parent.left
                anchors.right: parent.right
                Text {
                    height: 30 * mystyle.dp
                    anchors.bottom: parent.bottom
                    text: "built-in types:"
                    font.bold: true
                    font.pixelSize: mystyle.textSize
                    verticalAlignment: Text.AlignVCenter
                    x: 10 * mystyle.dp
                }
            }

            Repeater{
                model: document.typeManager.builtinTypes
                ModuleTypeListEntry {
                    moduleType: modelData
                    onAddClicked: addModuleClicked(modelData)
                    onInspectClicked: inspectModuleTypeClicked(moduleType)
                }
            }
        }
    }
}
