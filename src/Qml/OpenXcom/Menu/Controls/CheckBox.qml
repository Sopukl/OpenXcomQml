import QtQuick
import QtQuick.Controls as QC
import QtQuick.Controls.impl

QC.CheckBox {
    id: ctrl
    implicitWidth: 100
    implicitHeight: 18
    font.pixelSize: 9
    opacity: enabled ? 1.0 : 0.3
    property int hOrientation: Qt.LeftToRight

    indicator: Rectangle {
        width: ctrl.height
        height: ctrl.height
        border.color: "#21be2b"
        color: "#00000000"

        anchors {
            left:  hOrientation === Qt.LeftToRight?parent.left:undefined
            leftMargin: leftPadding
            right: hOrientation === Qt.RightToLeft?parent.right:undefined
            rightMargin: rightPadding
            verticalCenter: parent.verticalCenter
        }

        IconImage {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            color: "#21be2b"
            source: "qrc:/Images/CheckboxOn.svg"
            visible: ctrl.checked
        }
    }

    contentItem: Item {
        anchors {
            left:  hOrientation === Qt.LeftToRight?indicator.right:parent.left
            leftMargin: hOrientation === Qt.LeftToRight?2:leftPadding
            right: hOrientation === Qt.RightToLeft?indicator.left:parent.right
            rightMargin: hOrientation === Qt.RightToLeft?2:rightPadding
            verticalCenter: parent.verticalCenter
        }
        Text {
            text: ctrl.text
            font: ctrl.font
            color: "#21be2b"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors.fill: parent
        }
    }
}
