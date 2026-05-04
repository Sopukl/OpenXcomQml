import QtQuick 2.15

Popup {
    id: ctrl
    width: Math.min(col.width + 10, 300)
    height: Math.min(col.height + 10, 180)
    required property string errorText
    Column {
        id: col
        anchors.centerIn: parent
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 10
            color: "white"
            text: errorText
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Close"
            onClicked: ctrl.destroy()
        }
    }
}
