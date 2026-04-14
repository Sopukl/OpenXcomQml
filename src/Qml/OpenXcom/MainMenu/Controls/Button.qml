import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Button {
    id: control
    implicitWidth: 80
    implicitHeight: 18
    text: "Button"

    background: Rectangle {
        visible: !control.flat || control.down || control.checked || control.highlighted
        color: control.palette.button
        // color: Color.blend(control.checked || control.highlighted ? control.palette.dark : control.palette.button,
        //                                                             control.palette.mid, control.down ? 0.5 : 0.0)
        border.color: "red"
        border.width: control.hovered ? 2 : 0
        radius: 0
    }

    palette {
        button: "#1C8064"
        buttonText: "#64CCBC"
    }
}
