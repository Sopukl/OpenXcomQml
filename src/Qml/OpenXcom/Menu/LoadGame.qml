import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import OpenXcom 1.0
import OpenXcom.Menu.Controls 1.0 as XC

XC.Popup {
    id: popup
    width: 320
    height: 200

    Item {
        anchors {
            fill: parent
            margins: 2
        }
        Text {
            id: caption
            font.pixelSize: 12
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: Game.language.get("STR_SELECT_GAME_TO_LOAD")
            height: contentHeight
        }

        Rectangle {
            id: header
            anchors {
                left: parent.left
                right: parent.right
                top: caption.bottom
            }
            height: 10
            color: "#00000000"
            border.color: "#FFFFFF"
            Rectangle {
                id: bl
                height: 10
                width: 200
                color: "blue"
                anchors.left: parent.left
                Row {
                    Text {
                        font.pixelSize: 8
                        text: "Name:"
                    }
                    Button {
                        width: 10
                        height: 10
                        display: Button.IconOnly
                        padding: 0
                        icon{
                            source: "qrc:/Images/Triangle.svg"
                            color: "red"

                        }
                        onClicked: {
                            if(rotation === 180)
                                rotation = 0
                            else
                                rotation = 180
                        }
                    }
                }
            }
            Rectangle {
                id: rd
                height: 10
                color: "red"
                anchors{
                    left: bl.right
                    right:parent.right
                }
            }

        }

        ListView {
            id: savesList
            anchors {
                top: header.bottom
                topMargin: 1
                bottom: description.top
                bottomMargin: 1
                left: parent.left
                right: parent.right
            }
            spacing: 1
            model: Game.saves()
            clip: true

            delegate: MouseArea {
                height: 10
                width: savesList.width
                hoverEnabled: true

                required property string fileName
                required property string details
                required property string displayName
                required property string isoDate
                required property string isoTime
                required property int index

                onContainsMouseChanged:
                    descTxt.text = containsMouse?details:""
                onClicked: savesList.currentIndex = index

                onDoubleClicked: {
                    Game.loadGame(fileName)
                    popup.close();
                }

                Rectangle {
                    anchors.fill: parent
                    color: (index===savesList.currentIndex)?"#800000FF":
                                                            "#80FF00FF"
                }

                Text {
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }
                    text: displayName
                    height: contentHeight
                    width: contentWidth
                    font.pixelSize: 8
                    color: "#FFFFFF"
                }
                Text {
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: delImg.left
                        rightMargin: 2
                    }
                    text: isoDate+':' + isoTime
                    height: contentHeight
                    width: contentWidth
                    font.pixelSize: 8
                    color: "#FFFFFF"
                }
                ColorImage {
                    id: delImg
                    width: height
                    anchors.right: parent.right
                    height: parent.height
                    source: "qrc:/Images/Delete.svg"
                    color: "#FFFFFF"
                }
            }
        }

        Item {
            id: description
            height: childrenRect.height
            anchors{
                bottom: btnCancel.top
                left: parent.left
                right: parent.right
            }


            Text {
                text: "Desc"
                anchors.left: parent.left
                font.pixelSize: 8
                color: "white"
            }

            Text {
                id: descTxt
                anchors.right: parent.right
                font.pixelSize: 8
                color: "white"
            }
        }

        XC.Button {
            id: btnDone
            text: Game.language.get("STR_OK")
            //onClicked: popup.close()
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.horizontalCenter
                rightMargin: 1
            }
        }
        XC.Button {
            id: btnCancel
            text: Game.language.get("STR_CANCEL")
            onClicked: popup.close()
            anchors{
                bottom: parent.bottom
                left: parent.horizontalCenter
                leftMargin: 1
                right: parent.right
            }
        }
    }
}
