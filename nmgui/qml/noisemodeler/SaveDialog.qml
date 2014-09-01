import QtQuick 2.2
import QtQuick.Dialogs 1.1

FileDialog {
    id: saveDialog
    title: "Save file"
    onAccepted: {
        //TODO enforce correct extension
        document.saveAsQmlUrl(saveDialog.fileUrl);
    }
    selectExisting: false
    nameFilters: ["Noise Modeler graphs (*.nm.json)", "All files (*)"]
}
