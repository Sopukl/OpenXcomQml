import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
Popup {
    id: popup
    property alias bgImage: _bgImage
    anchors.centerIn: parent
    modal: true
    padding: 0
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    onOpened: forceActiveFocus()
    background: Image {
        id: _bgImage
        anchors.centerIn: parent
        transformOrigin: Item.Center
        scale: Options1.interfaceScale
        visible: source !== ""
        width: 320
        height: 200
        source: "image://xcom/mainMenu"
    }

    contentItem {
        transformOrigin: Item.Center
        scale: Options1.interfaceScale
    }

    Rectangle {
        anchors.fill: contentItem
        color: "#00000000"
        border {
            width: 1
            color: "green"
        }
        z: 999
    }
    onClosed: destroy()
}
