import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
Popup {
    id: popup
    property alias bgImage: _bgImage
    anchors.centerIn: parent
    width: _content.width
    height: _content.height
    modal: true
    padding: 0
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    scale: Options1.interfaceScale
    clip: true

    transformOrigin: Item.TopLeft
    Image {
        id: _bgImage
        anchors.centerIn: parent
        visible: source !== ""
        width: 320
        height: 200
        source: "image://xcom/mainMenu"
    }

    Rectangle {
        anchors.fill: parent
        color: "#00000000"
        border {
            width: 1
            color: "green"
        }
        z: 999
    }
    onClosed: destroy()
}
