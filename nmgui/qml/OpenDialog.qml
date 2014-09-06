import QtQuick 2.2
import QtQuick.Dialogs 1.1

FileDialog {
    id: openDialog
    title: "Open file"
    onAccepted: {
        console.log("TODO: open " + openDialog.fileUrl);
        document.openQmlUrl(openDialog.fileUrl);
    }
    nameFilters: ["Noise Modeler graphs (*.nm.json)", "All files (*)"]
}
