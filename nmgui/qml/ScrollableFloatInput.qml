import QtQuick 2.2

Item {
    id: scrollableFloatInput
    property real monitoredValue: 0
    signal newAcceptableValue(real value)
    implicitHeight: lineInput.implicitHeight
    height: lineInput.height
    onMonitoredValueChanged: {
        if(!lineInput.textInput.focus){
            var val = monitoredValue;
            lineInput.text = val%1 !== 0 ? val.toFixed(3) : val;
        }
    }

    LineInput {
        id: lineInput
        anchors.fill: parent
        text: monitoredValue%1 !== 0 ? monitoredValue.toFixed(3) : monitoredValue;
        anchors.left: parent.left
        anchors.right: parent.right
        validator: DoubleValidator{}
        onNewAcceptableValue: {
            var newValue = parseFloat(newText);
            scrollableFloatInput.newAcceptableValue(newValue);
        }
    }
    MouseArea {
        visible: !lineInput.readOnly
        anchors.fill: lineInput
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        onWheel: {
            wheel.accepted = true;
            //TODO: use wheel.pixelDelta for pixel perfect scrolling
            var wheelSensitivity = 1/1200;

            var newValue = monitoredValue * (1 + wheel.angleDelta.y*wheelSensitivity *
                    (monitoredValue<0?-1:1)); //flip direction of scrolling for negative values

            //if the value is very small, jump to something a bit more interesting
            if(Math.abs(newValue)<0.0001)newValue = wheel.angleDelta.y > 0 ? 0.01 : -0.01;
            scrollableFloatInput.newAcceptableValue(newValue);

            //change the text if it is currently focused, since this won't be done automatically in that case
            if(lineInput.textInput.focus)lineInput.text = newValue.toFixed(3);
        }
    }
}
