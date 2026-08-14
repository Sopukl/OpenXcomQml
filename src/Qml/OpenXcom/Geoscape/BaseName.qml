import QtQuick 2.15
import OpenXcom 1.0
import "../Controls" as XC

XC.Dialog {
    id: ctrl
    width: 192
    height: 80
    closePolicy: XC.Popup.NoAutoClose
    property alias baseName: ti.text
    signal done();

    Column {
        anchors.centerIn: parent
        spacing: 2
        TextInput {
            id: ti
            width: okBtn.width
            height: okBtn.height
            font: okBtn.font
            color: "white"
            focus: true
        }
        XC.Button {
            id: okBtn
            text: "Ok"
            enabled: ti.text !== ""
            onClicked: ctrl.done();
            focusPolicy: Qt.NoFocus
        }
    }
}
