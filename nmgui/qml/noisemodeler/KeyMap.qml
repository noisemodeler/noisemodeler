import QtQuick 2.2

Item{
    id: keyMap
    property var keys: ({})
    Keys.onPressed: {
        keys[event.key] = true;
    }
    Keys.onReleased: {
        keys[event.key] = false;
    }
    function isKeyDown(key){
        return keys[key] === true;
    }
}
