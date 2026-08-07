import QtQuick
import OpenXcom 1.0

Popup {
    id: popup
    width: 256
    height: 100
    signal accepted();
    Item {
        anchors {
            fill: parent
            margins: 2
        }
        Text {
            anchors.fill: parent
            text: Game.language.get("STR_IS_IT_OK_TO_DELETE_THE_SAVED_GAME")
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            clip: true
            color: "white"
        }
        Button {
            id: btnDone
            text: Game.language.get("STR_OK")
            onClicked: {
                accepted()
                close()
            }
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.horizontalCenter
                rightMargin: 1
            }
        }
        Button {
            id: btnCancel
            text: Game.language.get("STR_CANCEL")
            onClicked: close()
            anchors{
                bottom: parent.bottom
                left: parent.horizontalCenter
                leftMargin: 1
                right: parent.right
            }
        }
    }

}
