import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Dialog {
    id: popup
    property alias bgImage: _bgImage
    anchors.centerIn: parent
    modal: true
    padding: 0
    closePolicy: Popup.CloseOnEscape
    onOpened: forceActiveFocus()
    background: Item {
        width: popup.width
        height: popup.height
        clip: true
        transformOrigin: Item.Center
        scale: Options1.interfaceScale
        Image {
            id: _bgImage
            anchors.centerIn: parent
            visible: source !== ""
            width: 320
            height: 200
            source: "image://xcom/Interface/mainMenu"
        }
    }

    MouseArea {
        anchors.fill: contentItem
        acceptedButtons: Qt.AllButtons
        focusPolicy: Qt.NoFocus
    }

    contentItem {
        transformOrigin: Item.Center
        scale: Options1.interfaceScale
    }

    Rectangle {
        width: popup.width
        height: popup.height
        anchors.centerIn: parent
        color: "#00000000"
        border {
            width: 1
            color: "green"
        }
        z: 999
    }
    onClosed: destroy()
}
