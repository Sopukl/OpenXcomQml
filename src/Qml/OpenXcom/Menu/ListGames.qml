import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: popup
    width: 320
    height: 200

    property bool editebleNames: false
    property bool sortByName: true
    property bool sortAscended: true

    property var saves: []
    signal acceptedSavedGame(int index);

    function initSavesList() {
        return [];
    }

    function updateSavesList() {
        let origin = initSavesList()
        let fSortByName = (a, b) => {
            let res = a.displayName.localeCompare(b.displayName)
            return sortAscended?res:!res
        }

        let fSortByDate = (a, b) => {
            let res = a.isoDateTime.localeCompare(b.isoDateTime)
            return sortAscended?res:!res
        }

        let sortFunc = sortByName?fSortByName
                                 :fSortByDate;

        let autoSaves = origin.filter((saveDesk)=>{return saveDesk.isAutoSave()})
                              .sort(sortFunc)

        let commonSaves = origin.filter((saveDesk)=>{return !saveDesk.isAutoSave()})
                                .sort(sortFunc)

        saves = [...autoSaves, ...commonSaves]
    }

    component SmallText: Text {
        font.pixelSize: 8
        color: "white"
    }
    component SortButton: Button {
        width: 10
        height: 10
        display: Button.IconOnly
        property bool selected
        padding: 1
        background: Rectangle {
            color: "#00000000"
            border.color: selected?"#FFFFFFFF"
                                  :"#80FFFFFF"
        }

        icon{
            source: selected?"qrc:/Images/Triangle.svg"
                            :""
            color: "#FFFFFFFF"
        }
        rotation: sortAscended?0:180
    }


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
                id: nameHeader
                height: 10
                width: 200
                anchors.left: parent.left
                Row {
                    SmallText {
                        text: Game.language.get("STR_NAME")
                    }
                    SortButton {
                        selected: sortByName
                        onClicked: {
                            if(sortByName)
                            {
                                sortAscended = !sortAscended
                            }
                            else
                            {
                                sortByName = true;
                                sortAscended = true;
                            }
                            updateSavesList()
                        }
                    }
                }
            }
            Item {
                id: dateHeader
                height: 10
                anchors{
                    left: nameHeader.right
                    right:parent.right
                }
                Row {
                    SmallText {
                        text: Game.language.get("STR_DATE")
                    }
                    SortButton {
                        selected: !sortByName
                        onClicked: {
                            if(sortByName)
                            {
                                sortByName = false;
                                sortAscended = true;
                            }
                            else
                            {
                                sortAscended = !sortAscended;
                            }
                            updateSavesList()
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
            clip: true
            model: saves
            property int highlightedIdx: -1
            highlight: Rectangle {
                color: "#4000FFFF"
            }

            delegate: MouseArea {
                height: 10
                width: savesList.width

                required property string fileName
                required property string details
                required property string displayName
                required property string isoDateTime
                required property int index

                onClicked: {
                    savesList.currentIndex = index
                }

                onDoubleClicked: {
                    acceptedSavedGame(index)
                    popup.close();
                }

                TextInput {
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }
                    font.pixelSize: 8
                    color: "white"
                    readOnly: !editebleNames
                    onActiveFocusChanged: {
                        if(activeFocus)
                            savesList.currentIndex = index
                    }

                    text: displayName
                    height: contentHeight
                    width: nameHeader.width
                }
                SmallText {
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: delImg.left
                        rightMargin: 2
                    }
                    text: isoDateTime
                    height: contentHeight
                    width: dateHeader.width
                }
                ColorImage {
                    id: delImg
                    width: height
                    anchors.right: parent.right
                    height: parent.height
                    source: "qrc:/Images/Delete.svg"
                    color: "#FFFFFF"
                    MouseArea {
                        anchors.fill: parent
                        function deleteAccepted()
                        {
                            Game.deleteSaveGame(fileName);
                            updateSavesList();
                        }
                        onClicked: {
                            let confirmPopup = Qt.createComponent("DeleteGame.qml")
                                                 .createObject(popup)
                            confirmPopup.accepted.connect(deleteAccepted)
                            confirmPopup.open()
                        }
                    }
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
                onPositionChanged: function(mouse)
                {
                    let pos = mapToItem(savesList.contentItem,
                                        Qt.point(mouse.x,mouse.y))
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

            SmallText {
                text: "Desc"
                anchors.left: parent.left
            }

            SmallText {
                id: descTxt
                anchors.right: parent.right
            }
        }

        XC.Button {
            id: btnDone
            text: Game.language.get("STR_OK")
            onClicked: acceptedSavedGame(savesList.currentIndex)
            enabled: savesList.currentItem
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
    Component.onCompleted: updateSavesList()
}
