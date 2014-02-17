import QtQuick 2.0

Rectangle {
    id: tooltip
    property alias text: textContainer.text
    property int padding: 3
    width: textContainer.width + padding * 2
    height: textContainer.height + padding * 2
    color: mystyle.toolTipBg
    z: 200
    Text {
        anchors.centerIn: parent
        id:textContainer
        text: "Gering geding ding ding!"
    }
    NumberAnimation {
        id: fadein
        target: tooltip
        property: "opacity"
        easing.type: Easing.InOutQuad
        duration: 300
        from: 0
        to: 1
    }
    NumberAnimation {
        id: fadeout
        target: tooltip
        property: "opacity"
        easing.type: Easing.InOutQuad
        from: 1
        to: 0
        onStopped: visible = false;
    }
    onVisibleChanged: if(visible)fadein.start();
    visible:false
    function show(){
        visible = true;
        fadein.start();
    }
    function hide(){
        fadeout.start();
    }
}
