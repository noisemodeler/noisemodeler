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
                anchors.fill: parent
                drag.target: offset
                hoverEnabled: true
                acceptedButtons: Qt.NoButton
                onWheel: {
                    wheel.accepted = true;
                    //TODO: use wheel.pixelDelta
                    values[modelData] *= 1.0 + -wheel.angleDelta.y/1200;
                    offset.y = -values[modelData];
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
