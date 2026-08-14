import QtQuick
import QtQuick.Controls

Slider {
    id: ctrl
    implicitWidth: 100
    implicitHeight: 18
    padding: 0
    font.pixelSize: 9
    from: 0
    to: 100

    background: Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: ctrl.width
        height: ctrl.height/2
        color: "#bdbebf"

        Rectangle {
            width: ctrl.visualPosition * parent.width
            height: parent.height
            color: "#21be2b"
        }
    }

    handle: Rectangle {
        x: ctrl.visualPosition * (ctrl.availableWidth - width)
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        color: ctrl.pressed ? "#f0f0f0" : "#f6f6f6"
        border.color: "#bdbebf"
        Text {
            font: ctrl.font
            text:  ctrl.value.toFixed()
            anchors.centerIn: parent
        }
    }
}
