import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

ApplicationWindow {
    Style { id: mystyle }
    visible: true
    width: Screen.desktopAvailableWidth * 0.8
    height: Screen.desktopAvailableHeight * 0.8
    title: "Noise Modeler"

    NoiseModelerApp {
        anchors.fill: parent
    }
}
