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
            font.pixelSize: 8
            color: "white"
            text: "Select save game for loading"
            height: contentHeight
        }

        ListView {
            id: savesList
            anchors {
                top: caption.bottom
                topMargin: 2
                bottom: description.top
                bottomMargin: 2
                left: parent.left
                right: parent.right
            }
            spacing: 1
            model: Game.saves()

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

                onDoubleClicked: Game.loadGame(fileName)

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
                bottom: btns.top
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
        Item {
            id: btns
            height: childrenRect.height
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }


            XC.Button {
                text: "Загрузить"
                onClicked: {
                    let curItem = savesList.currentItem
                    if(curItem)
                        Game.loadGame(curItem.fileName)
                }
                anchors.left: parent.left
            }

            XC.Button {
                text: "Отмена"
                onClicked: popup.close()
                anchors.right: parent.right
            }
        }
    }
}
