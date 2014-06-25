import QtQuick 2.2
import NoiseModeler 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

SubWindow {
    id: heightMap3DExplorerWindow
    property bool maximized: false
    resizeContents: maximized
    windowTitle: "heightmap 3D preview"
    width: maximized ? mainArea.width : colLayout.implicitWidth
    height: maximized ? mainArea.height : colLayout.implicitHeight + titleBar.height

    ColumnLayout{
        spacing: 0
        id: colLayout
        width: maximized ? heightMap3DExplorerWindow.width : undefined
        height: maximized ? heightMap3DExplorerWindow.height - titleBar.height: undefined
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitWidth: 350
            implicitHeight: 350
            HeightMap3DExplorer {
                anchors.fill: parent
                id: renderer
                heightMapFunction: HeightMapFunction {
                    inputLink: document.typeManager.userTypes[0].graph.findModule("inputs").inputs[0];
                    outputLink: document.typeManager.userTypes[0].graph.findModule("outputs").outputs[0];
                }
                texturingEnabled: true
                Keys.forwardTo: keyMap
            }

            Item {
                id: cameraKeyboardControls
                anchors.fill: renderer
                KeyMap {
                    id: keyMap
                }
                Timer {
                    running: true; repeat: true
                    interval: 10
                    onTriggered: {
                        //yawing/turning
                        var yawDir = -keyMap.getAxis(Qt.Key_Right, Qt.Key_Left);
                        var yawSpeed = 80;
                        if(yawDir!==0)renderer.yawCamera(yawDir * yawSpeed * interval/1000);

                        //pitching/tilting
                        var pitchDir = keyMap.getAxis(Qt.Key_Up, Qt.Key_Down);
                        var pitchSpeed = 80;
                        if(pitchDir!==0)renderer.pitchCamera(-pitchDir * pitchSpeed * interval/1000);

                        //forwards/backwards
                        var forwardDir = keyMap.getAxis(Qt.Key_W, Qt.Key_S);
                        var forwardSpeed = 64;
                        if(forwardDir!==0)renderer.moveCameraForward(forwardDir * forwardSpeed * interval/1000);

                        var strafeDir = keyMap.getAxis(Qt.Key_D, Qt.Key_A);
                        var strafeSpeed = 64;
                        if(strafeDir!==0)renderer.moveCameraRight(strafeDir * strafeSpeed * interval/1000);
                    }
                }
            }
            MouseArea {
                drag.target: offset
                Item {
                    property real lastX
                    property real lastY
                    property real yawSensitivity: 0.2
                    property real pitchSensitivity: 0.2
                    id: offset
                    onXChanged: {
                        var deltaX = x-lastX;
                        renderer.yawCamera(-deltaX*yawSensitivity);
                        lastX = x;
                    }
                    onYChanged: {
                        var deltaY = y-lastY;
                        renderer.pitchCamera(-deltaY*pitchSensitivity);
                        lastY = y;
                    }
                }
                anchors.fill: renderer
                onDoubleClicked: maximized = !maximized
                onPressedChanged: renderer.forceActiveFocus(); //renderer.focus = true;
            }
        }
        GridLayout {
            Layout.fillWidth: true
            rowSpacing: 5
            columnSpacing: 5
            columns: 8
            flow: GridLayout.LeftToRight

            Item{width:5}
            Text {
                Layout.column: 1
                text: "x:"
            }
            ScrollableFloatInput {
                monitoredValue: renderer.center.x
                Layout.minimumWidth: 50
                Layout.fillWidth: true
                onNewAcceptableValue: renderer.center.x = value;
            }
            Text {
                text: "width scale:"
            }
            ScrollableFloatInput {
                monitoredValue: renderer.widthScale
                Layout.minimumWidth: 50
                Layout.fillWidth: true
                onNewAcceptableValue: renderer.widthScale = value;
            }
            Item{width:1} Item{width:1} Item{width:5} Item{width:5}
            Text {
                text: "y:"
            }
            ScrollableFloatInput {
                monitoredValue: renderer.center.y
                Layout.minimumWidth: 50
                Layout.fillWidth: true
                onNewAcceptableValue: renderer.center.y = value;
            }
            Text {
                text: "height scale:"
            }
            ScrollableFloatInput {
                monitoredValue: renderer.heightScale
                Layout.minimumWidth: 50
                Layout.fillWidth: true
                onNewAcceptableValue: renderer.heightScale = value;
            }
            Text {
                text: "texturing"
            }
            Rectangle {
                property bool checked: renderer.texturingEnabled
                width: 10
                height: 10
                color: "white"
                MouseArea {
                    anchors.fill: parent
                    onClicked: renderer.texturingEnabled = !parent.checked;
                }
                Rectangle{
                    visible: parent.checked
                    color: "blue"
                    anchors.centerIn: parent
                    width: 8
                    height: 8
                }
            }
        }
    }
}
