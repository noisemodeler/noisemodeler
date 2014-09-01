import QtQuick 2.2
import QtQuick.Layouts 1.1

Text {
    font.pixelSize: mystyle.textSize
    id: inspectorLabel
    Layout.maximumWidth: 50 * mystyle.dp
    Layout.minimumWidth: 50 * mystyle.dp
    elide: Text.ElideRight
}
