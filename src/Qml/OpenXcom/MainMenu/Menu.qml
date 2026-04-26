import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC

Item {
    id: ctrl
    width: 256
    height: 160
    anchors.centerIn: parent
    clip: true

    component MenuButton: XC.Button {
        width: 92
        height: 20
        font.pixelSize: 12
    }

    Image {
        anchors.centerIn: parent
        width: 320
        height: 200
        source: "image://xcom/mainMenu"
    }
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border {
            width: 2
            color: "green"
        }
    }

    MenuButton {
        text: "New Game"
        x: 32
        y: 70
        onClicked: {
            Xcom.createWindow("MainMenu/NewGame.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "New Battle"
        x: 132
        y: 70
        onClicked: {
            Xcom.createWindow("MainMenu/NewBattle.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Load Game"
        x: 32
        y: 98
        onClicked: {
            Xcom.createWindow("MainMenu/LoadGame.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Options"
        x: 132
        y: 98
        onClicked: {
            Xcom.createWindow("MainMenu/Options.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Mods"
        x: 32
        y: 124
        onClicked: {
            Xcom.createWindow("MainMenu/Mods.qml", ctrl)
                .open()
        }
    }
    MenuButton {
        text: "Quit"
        x: 132
        y: 124
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 16
        text: "OpenXcom\nversion: blablabla"
        y: 15
        color: "white"
        horizontalAlignment: Text.AlignHCenter

    }
}

