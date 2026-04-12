import QtQuick
import QtQuick.Controls

Item {
    width: 256
    height: 160
    anchors.centerIn: parent

    component MenuButton: Button {
        width: 92
        height: 20
        font.pixelSize: 12
    }

    Rectangle {
        anchors.fill: parent
        color: "blue"
        opacity: 0.5
    }

    MenuButton {
        text: "New Game"
        x: 32
        y: 70
    }
    MenuButton {
        text: "New Battle"
        x: 132
        y: 70
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
}
