import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Dialog {
    id: popup
    property alias bgImage: _bgImage
    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0
    topMargin: 0
    bottomMargin: 0
    leftMargin: 0
    rightMargin: 0
    topInset: 0
    bottomInset: 0
    leftInset: 0
    rightInset: 0

    anchors.centerIn: parent
    modal: true
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
    enter: Transition {
        ParallelAnimation {
            NumberAnimation { property: "scale"; from: 0.0; to: 1.0; duration: 200; }
            NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 200 }
        }
    }

    exit: Transition {
        ParallelAnimation {
            NumberAnimation { property: "scale"; from: 1.0; to: 0.0; duration: 200;}
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 200 }
        }
    }
}
