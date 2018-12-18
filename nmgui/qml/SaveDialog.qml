import QtQuick 2.2
//import QtQuick.Dialogs 1.2
import Qt.labs.platform 1.0

FileDialog {
    id: saveDialog
    title: "Save file"
    onAccepted: {
        let url = files[0];
        // TODO: This is needed due to a bug in Qt (it doesn't handle double extensions properly)
        if (!url.endsWith(".nm.json")) {
            url += ".nm.json";
        }
        document.saveAsQmlUrl(url);
    }
    fileMode: FileDialog.SaveFile
    nameFilters: ["Noise Modeler graphs (*.nm.json)"] // "All files (*)"] // TODO: comment in again when Qt bug is fixed
}
