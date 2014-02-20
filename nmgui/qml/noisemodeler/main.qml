import QtQuick 2.2

Rectangle {
    Style { id:mystyle }
    width: 800
    height: 600
    TopBar {
        id: menu
        z: 100
    }

    ModuleTypeBrowser {
        z:50
        id: moduleTypeBrowser
    }

    Item {
        id: mainArea
        anchors.top: menu.bottom
        anchors.left: moduleTypeBrowser.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    GraphEditor{
        id: editor
        anchors.fill: mainArea
        model: mockGraph
    }
    Keys.onPressed: {
        if(event.key === Qt.Key_F){
            editor.autoArrangeWindows();
        }
    }
}
