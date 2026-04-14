import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
Popup {
    id: popup
    default property alias children : _content.children
    property alias bgImage: _bgImage
    anchors.centerIn: parent
    width: _content.width
    height: _content.height
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Item {
        width: popup.width
        height: popup.height
        anchors.centerIn: parent
        scale: Options1.interfaceScale
        clip: true
        Image {
            id: _bgImage
            anchors.centerIn: parent
            visible: source !== ""
        }
        Item {
            id: _content
            width: popup.width
            height: popup.width
            clip: true
        }

        Rectangle {
            anchors.fill: parent
            color: "#00000000"
            border {
                width: 1
                color: "green"
            }
        }
    }
    onClosed: destroy()
}
