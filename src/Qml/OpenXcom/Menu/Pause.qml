import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: ctrl
    width:  216
    height: 160
    property bool isIronMan: Game?.savedGame?.isIronMan??false

    component PButton: XC.Button {
        width: 180
        height: 18
        font.pixelSize: 12
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: enabled?1.0:0.3
    }


    Column {
        spacing: 5
        anchors {
            centerIn: parent
        }
        Text {
            id: caption
            text: Game.language.get("STR_OPTIONS_UC")
            font.pixelSize: 20
            color: "yellow"

            anchors.horizontalCenter: parent.horizontalCenter
        }
        Item {
            width: 1
            height: 5
        }
        PButton {
            text: Game.language.get("STR_LOAD_GAME")
            enabled: !isIronMan
            onClicked: {
                let loadGameDlg = Xcom.createWindow("Menu/LoadGame.qml", ctrl)
                loadGameDlg.accepted.connect(ctrl.close)
                loadGameDlg.open()
            }
        }
        PButton {
            text: Game.language.get("STR_SAVE_GAME")
            enabled: !isIronMan
            onClicked: {
                let loadGameDlg = Xcom.createWindow("Menu/SaveGame.qml", ctrl)
                loadGameDlg.accepted.connect(ctrl.close)
                loadGameDlg.open()
            }

        }
        PButton {
            text: Game.language.get(isIronMan?
                    "STR_SAVE_AND_ABANDON_GAME":
                    "STR_ABANDON_GAME")
            onClicked: {
                isIronMan?Game.abandonAndSaveGame()
                         :Game.abandonGame();
                close();
            }
        }
        PButton {
            text: Game.language.get("STR_GAME_OPTIONS")
            onClicked: {
                Xcom.createWindow("Menu/Options.qml", ctrl)
                    .open()
            }
        }
        PButton {
            text: Game.language.get("STR_CANCEL_UC")
            onClicked: close()
        }
    }
}