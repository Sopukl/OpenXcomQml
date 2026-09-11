import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: ctrl
    width: 256
    height: 160
    anchors.centerIn: parent

    component MenuButton: XC.Button {
        width: 92
        height: 20
        font.pixelSize: 12
    }

    MenuButton {
        text: "New Game"
        x: 32
        y: 60
        onClicked: {
            let newGameDlg = Xcom.createWindow("Menu/NewGame.qml", ctrl);
            newGameDlg.accepted.connect(ctrl.close)
            newGameDlg.open()
        }
    }
    MenuButton {
        text: "New Battle"
        x: 132
        y: 60
        onClicked: {
            Xcom.createWindow("Menu/NewBattle.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Load Game"
        x: 32
        y: 88
        onClicked: {
            let loadGameDlg = Xcom.createWindow("Menu/LoadGame.qml", ctrl)
            loadGameDlg.accepted.connect(ctrl.close)
            loadGameDlg.open()
        }
    }
    MenuButton {
        text: "Options"
        x: 132
        y: 88
        onClicked: {
            Xcom.createWindow("Menu/Options.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Mods"
        x: 32
        y: 114
        onClicked: {
            Xcom.createWindow("Menu/Mods.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Quit"
        x: 132
        y: 114

        onClicked: Game.quit();
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16
        text: "OpenXcom\nversion: blablabla"
        y: 5
        color: "white"
        horizontalAlignment: Text.AlignHCenter

    }
}
