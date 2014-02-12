import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id:graphEditor
    color: mystyle.graphEditor.bgColor

    Node{module:mockModule}
    Node{module:mockModule2}
    Node{module:mockModule3}
    TexturePreview{}
}
