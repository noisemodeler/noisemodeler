import QtQuick 2.2

Text{
    width: maximized ? undefined : 40
    elide: Text.ElideRight
    anchors.verticalCenter: parent.verticalCenter
    anchors.margins: 3
    text: ''
    font.pointSize: mystyle.smallTextSize
}
