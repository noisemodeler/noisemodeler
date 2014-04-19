import QtQuick 2.2
import NoiseModeler 1.0

Rectangle {
    id: graphEditor
    color: mystyle.graphEditor.bgColor
    property alias contents: contents
    property Graph graph
    property variant selectedModule

    //TODO remove this
    function reload(){
        contents.clearContents();
        contents.updateContents();
        autoArrangeWindows();
    }

    MouseArea {
        anchors.fill: parent
        drag.target: contents
        acceptedButtons: Qt.RightButton | Qt.MiddleButton
    }
    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onPressed: graphEditor.focus = true; //remove focus from children if background in graph editor is clicked
    }

    onGraphChanged: {
        //TODO disconnect old signal
        graph.onModulesChanged.connect(contents.updateContents);
        graph.onModuleRemoved.connect(contents.onModuleRemoved);
        graph.onModuleAdded.connect(contents.addNode);
    }
    Component.onCompleted: {
        if(graph){
            contents.updateContents();
            autoArrangeWindows();
        }
    }

    Component {
        id: nodeDelegate
        Node {
            onSelectedChanged: {
                if(selected)selectedModule = module;
            }
        }
    }

    Item {
        id: contents
        function addNode(name, index){
            var module = graph.modules[index];
            nodeDelegate.createObject(contents, {"module":module});
        }
        function onModuleRemoved(name, index){
            children[index].destroy();
        }

        function clearContents(){
            for(var i=0; i<children.length; i++){
                children[i].destroy();
            }
        }

        function updateContents(){
            for(var i=0; i<graph.modules.length; ++i){
                var module = graph.modules[i];
                if(children.length > i){
                    if(children[i].module === module){
//                        console.log("node exists for this object")
                    } else {
                        console.log("Unexpected child: "+children[i]);
                    }
                } else {
                    addNode(module.name, i);
                }

            }
        }
    }

    TexturePreview {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }
    HeightMap3DExplorerWindow {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
    }
    function autoArrangeWindows(){
        contents.x = 0;
        contents.y = 0;

        //sort nodes according to depth
        var columns = [];
        for(var i=0; i<contents.children.length; ++i){
            var node = contents.children[i];
            var depth = node.module.getDepth();
            if(!columns.hasOwnProperty(depth)){
                columns[depth] = []
            }
            columns[depth][node.module.name] = node;
        }

        //place each depth into its own column
        var curX = 50;
        for(var depth = 0; depth<columns.length; ++depth){
            var curY = 50;
            //adjust column width according to the biggest node
            var maxWidth = 0;
            for(var moduleName in columns[depth]){
                var node = columns[depth][moduleName];
                node.x = curX;
                node.y = curY;
                curY += node.height + 50;
                maxWidth = Math.max(maxWidth, node.width);
            }
            curX+= maxWidth + 70;
        }
    }
}
