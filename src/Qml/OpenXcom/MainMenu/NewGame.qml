import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC

XC.Popup {
    id: popup
    anchors.centerIn: parent
    width: 192
    height: 180

    Column {
        anchors.centerIn: parent
        spacing: 2
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Difficulty level"
            color: "white"
        }
        ListView {
            id: diffList
            orientation: ListView.Vertical
            interactive: false
            spacing: 2
            width:  160
            height: 100
            currentIndex: 0
            model: [{text:"Beginner",   value:0},
                    {text:"Experienced",value:1},
                    {text:"Veteran",    value:2},
                    {text:"Genius",     value:3},
                    {text:"Superhuman", value:4}]

            delegate: XC.Button {
                width: 160
                text: modelData.text
                onClicked: diffList.currentIndex = index
            }
            highlight: Rectangle {
                color: "green"
                opacity: 0.5
                z: 1
            }
        }
        CheckBox {
            id: ironCheckBox
            width: 160
            height: 18
            checked: false
            text: "Ironman"
            palette.windowText: "white"
        }
        Row {
            spacing: 5
            XC.Button {
                width: 78
                text: "Ok"
                onClicked: {
                    Game.newGame(diffList.model[diffList.currentIndex].value,
                                 ironCheckBox.checked)
                    popup.close()
                }
            }
            XC.Button {
                width: 78
                text: "Cancel"
                onClicked: popup.close()
            }
        }
    }
}
