import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Button {
    id: control
    implicitWidth: 80
    implicitHeight: 18
    text: "Button"

    background: Rectangle {
        color: control.palette.button
        radius: 0
    }

    contentItem: Text {
        font.pixelSize: 10
        color: "#64CCBC"
        text: control.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    palette {
        button: "#A01C8064"
        buttonText: "#64CCBC"
    }
}
