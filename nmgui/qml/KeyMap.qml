import QtQuick 2.2

Item{
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
    function getAxis(positiveKey, negativeKey){
        var direction = 0;
        direction += isKeyDown(positiveKey) ? 1 : 0;
        direction -= isKeyDown(negativeKey) ? 1 : 0;
        return direction;
    }
}
