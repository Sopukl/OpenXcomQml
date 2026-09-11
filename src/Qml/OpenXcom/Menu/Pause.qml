import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: root
    width:  216
    height: 160

    component PButton: XC.Button {
        width: 180
        height: 18
        font.pixelSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: caption
        text: Game.language.get("STR_OPTIONS_UC")
        font.pixelSize: 20
        color: "yellow"

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
        }
    }

    Column {
        spacing: 5
        anchors {
            top: caption.bottom
            horizontalCenter: caption.horizontalCenter
        }

        PButton { text: Game.language.get("STR_LOAD_GAME") }
        PButton { text: Game.language.get("STR_SAVE_GAME") }
        PButton { text: Game.language.get("STR_ABANDON_GAME") }
        PButton { text: Game.language.get("STR_GAME_OPTIONS") }
        PButton { text: Game.language.get("STR_CANCEL_UC") }
    }
}