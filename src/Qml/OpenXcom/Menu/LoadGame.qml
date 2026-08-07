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

        Item {
            id: header
            anchors {
                left: parent.left
                right: parent.right
                top: caption.bottom
            }
            height: 10
            Item {
                id: bl
                height: 10
                width: 200
                anchors.left: parent.left
                Row {
                    Text {
                        font.pixelSize: 8
                        color: "white"
                        text: Game.language.get("STR_NAME")
                    }
                    Button {
                        width: 10
                        height: 10
                        display: Button.IconOnly
                        padding: 0
                        icon{
                            source: "qrc:/Images/Triangle.svg"
                            color: "white"

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
            Item {
                id: rd
                height: 10
                anchors{
                    left: bl.right
                    right:parent.right
                }
                Row {
                    Text {
                        font.pixelSize: 8
                        color: "white"
                        text: Game.language.get("STR_DATE")
                    }
                    Button {
                        width: 10
                        height: 10
                        display: Button.IconOnly
                        padding: 0
                        icon{
                            source: "qrc:/Images/Triangle.svg"
                            color: "white"

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
            model: Game.saves()
            clip: true
            property int highlightedIdx: -1

            delegate: MouseArea {
                height: 10
                width: savesList.width

                required property string fileName
                required property string details
                required property string displayName
                required property string isoDate
                required property string isoTime
                required property int index

                onContainsMouseChanged:
                    descTxt.text = containsMouse?details:""
                onClicked: {
                    savesList.currentIndex = index
                    Game.loadGame(fileName)
                    popup.close();
                }

                onDoubleClicked: {
                    Game.loadGame(fileName)
                    popup.close();
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
                Rectangle {
                    anchors.fill: parent
                    color: "white"
                    opacity: (index === savesList.highlightedIdx)?0.2:0.0
                }
            }
            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                hoverEnabled: true
                onPressed: function(mouse){mouse.accepted = false;}
                onWheel: function(wheel){wheel.accepted = false}
                onPositionChanged: (mouse)=>{

                    let pos = mapToItem(savesList.contentItem, Qt.point(mouse.x,mouse.y))
                    let idx = savesList.indexAt(pos.x, pos.y);
                    if(idx !== -1)
                    {
                        descTxt.text = savesList.itemAtIndex(idx).details
                        savesList.highlightedIdx = idx;
                    }

                    mouse.accepted = false
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
