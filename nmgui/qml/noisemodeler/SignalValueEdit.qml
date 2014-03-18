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

        LineInput {
            id: lineInput
            Layout.fillWidth: true
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
                        text= val%1 !== 0 ? val.toFixed(3) : val;
                    }
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
