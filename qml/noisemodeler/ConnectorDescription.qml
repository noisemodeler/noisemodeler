import QtQuick 2.2

Text{
    width: 30
    anchors.left: connector.right
    elide: Text.ElideRight
    anchors.verticalCenter: parent.verticalCenter
    anchors.margins: 3
    text: ''
}
