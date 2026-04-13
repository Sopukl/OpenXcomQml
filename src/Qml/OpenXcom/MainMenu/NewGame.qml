import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
Popup {
    id: popup
    anchors.centerIn: parent
    width: 192
    height: 180
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Item {
        width: 192
        height: 180
        anchors.centerIn: parent
        scale: Options1.interfaceScale
        clip: true
        Image {
            anchors.centerIn: parent
            width: 320
            height: 200
            source: "image://xcom/mainMenu"
        }
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
                spacing: 2
                width:  160
                height: 100
                currentIndex: 0
                model: [{text:"Beginner",   value:0},
                        {text:"Experienced",value:1},
                        {text:"Veteran",    value:2},
                        {text:"Genius",     value:3},
                        {text:"Superhuman", value:4}]

                delegate: Button {
                    width: 160
                    height: 18
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
                Button {
                    width: 78
                    height: 18
                    text: "Ok"
                    onClicked: {
                        Game.newGame(diffList.model[diffList.currentIndex].value,
                                     ironCheckBox.checked)
                        popup.close()
                    }
                }
                Button {
                    width: 78
                    height: 18
                    text: "Cancel"
                    onClicked: popup.close()
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "#00000000"
            border {
                width: 1
                color: "green"
            }
        }
    }
    onClosed: destroy()
}
