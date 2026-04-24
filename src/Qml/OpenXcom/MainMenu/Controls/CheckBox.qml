import QtQuick
import QtQuick.Controls

CheckBox {
    id: ctrl
    implicitWidth: 100
    implicitHeight: 18
    font.pixelSize: 9
    indicator: Rectangle {
        width: ctrl.height
        height: ctrl.height
        border.color: "#21be2b"

        IconImage {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            color: "#21be2b"
            source: "qrc:/Images/CheckboxOn.svg"
            visible: ctrl.checked
        }
    }

    contentItem: Text {
        text: ctrl.text
        font: ctrl.font
        opacity: enabled ? 1.0 : 0.3
        color: "#21be2b"
        verticalAlignment: Text.AlignVCenter
        leftPadding: ctrl.indicator.width + ctrl.spacing
    }
}
