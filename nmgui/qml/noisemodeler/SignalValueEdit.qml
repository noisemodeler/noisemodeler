import QtQuick 2.2
import QtQuick.Layouts 1.1

RowLayout {
    id: signalValueEdit
    property int fields: 1
    property bool readOnly: false
    property var values: [0,0,0,0]
    signal valueChanged(int index, var values)

    Repeater {
        id:repeater
        model: fields

        Item {
            Layout.fillWidth: true
            height: lineInput.height
            LineInput {
                id: lineInput
                anchors.left: parent.left
                anchors.right: parent.right
                readOnly: signalValueEdit.readOnly
                validator: DoubleValidator{}
                onNewAcceptableValue: {
                    var newValue = parseFloat(newText);
                    values[modelData] = newValue;
                    valueChanged(modelData, values);
                }
                Connections {
                    target: signalValueEdit
                    onValuesChanged: {
                        if(!lineInput.textInput.focus){
                            var val = values[modelData];
                            lineInput.text = val%1 !== 0 ? val.toFixed(3) : val;
                        }
                    }
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
                    values[modelData] *= 1.0 + wheel.angleDelta.y*wheelSensitivity *
                            (values[modelData]<0?-1:1); //flip direction of scrolling for negative values
                    if(Math.abs(values[modelData])<0.0001)values[modelData] += wheel.angleDelta.y > 0 ? 0.01 : -0.01;
                    valueChanged(modelData, values);
                    lineInput.text = values[modelData].toFixed(3);
                }
            }
        }
    }

    function updateValue(newValue){
        values[0] = newValue.x;
        values[1] = newValue.y;
        values[2] = newValue.z;
        values[3] = newValue.w;
        valuesChanged(values);
    }
}
