import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Item {
    id: ctrl
    width: 256
    height: 160
    anchors.centerIn: parent
    clip: true

    component MenuButton: Button {
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
            Qt.createComponent("NewGame.qml")
              .createObject(ctrl)
              .open()
        }
    }
    MenuButton {
        text: "New Battle"
        x: 132
        y: 70
        onClicked: {
            Qt.createComponent("NewBattle.qml")
              .createObject(ctrl)
              .open()
        }
    }
    MenuButton {
        text: "Load Game"
        x: 32
        y: 98
    }
    MenuButton {
        text: "Options"
        x: 132
        y: 98
    }
    MenuButton {
        text: "Mods"
        x: 32
        y: 124
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

    // NewGame {
    //     id: newGamePopup
    //     visible: false
    // }
}

