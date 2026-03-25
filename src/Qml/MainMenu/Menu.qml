import QtQuick
import QtQuick.Controls

Item {
    width: 760
    height: 480
    Rectangle {
        anchors.fill: parent
        color: "red"
        opacity: 0.5
        border {
            width: 6
            color: "blue"
        }
    }

    Column {
        anchors.centerIn: parent
        Text {
            font.pixelSize: 48
            anchors.horizontalCenter: parent.horizontalCenter
            text: "OpenXcom"
            color: "white"
        }
        Text {
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
            text: "OpenXcom QML version 8.5.6"
            color: "white"
        }

        spacing: 20
        Grid {
            columns: 2
            spacing: 20

            Button {
                width: 275
                height: 60
                text: "Новая игра"
            }
            Button {
                width: 275
                height: 60
                text: "Новая битва"
            }
            Button {
                width: 275
                height: 60
                text: "Загрузить игру"
            }
            Button {
                width: 275
                height: 60
                text: "Настройки"
            }
            Button {
                width: 275
                height: 60
                text: "Моды"
            }
            Button {
                width: 275
                height: 60
                text: "Выход"
            }
        }
    }
}
