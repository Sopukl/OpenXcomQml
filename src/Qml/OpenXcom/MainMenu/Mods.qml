import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC

XC.Popup {
    id: ctrl
    width: 320
    height: 200
    anchors.centerIn: parent
    property var mods: [...Game.getModsInfo()]

    function moveUp(idx) {
        if(idx > 0)
        {
            let cur = mods[idx];
            mods.splice(idx, 1);
            mods.splice(idx-1, 0, cur);
            ctrl.modsChanged();
        }
    }

    onModsChanged: {
        console.log("----");
        for(let o of mods)
            console.log(o.name)
    }

    // ========== ЗАГОЛОВОК "BASE GAME" ==========
    Text {
        id: masterLabel
        text: "BASE GAME"
        color: "white"
        font.pixelSize: 9
        anchors {
            top: parent.top
            topMargin: 8
            left: parent.left
            leftMargin: 8
        }
    }

    // ========== КОМБОБОКС МАСТЕР-МОДОВ ==========
    XC.ComboBox {
        id: masterCombo
        width: 305
        height: 18
        anchors {
            top: masterLabel.bottom
            topMargin: 2
            left: parent.left
            leftMargin: 8
        }

        displayText: currentValue?.name??"undefined"
        function formatText(index) {
            return model[index]?.name??"undefined"
        }

        model: mods.filter(mod=>mod.isMaster)
        currentIndex: model.findIndex(mod=>mod.enabled)
    }

    // ========== ЗАГОЛОВКИ ТАБЛИЦЫ ==========
    Row {
        id: tableHeader
        width: 288
        height: 16
        anchors {
            top: masterCombo.bottom
            topMargin: 6
            left: parent.left
            leftMargin: 8
        }
        spacing: 2

        Text {
            width: 200
            text: "Mod Name"
            color: "#aaaaaa"
            font.pixelSize: 8
        }
        Item {
            width: 25
        }
        Text {
            width: 60
            text: "Enabled"
            color: "#aaaaaa"
            font.pixelSize: 8
            horizontalAlignment: Text.AlignRight
        }
    }

    // ========== СПИСОК МОДОВ ==========
    ListView {
        id: modsList
        width: 288
        height: 104
        anchors {
            top: tableHeader.bottom
            left: parent.left
            leftMargin: 8
        }
        clip: true

        model: {
            let master = masterCombo.currentValue;
            return master?mods.filter(mod=>mod.masterId === master.id):[]
        }

        delegate: Item {
            id: delegateItem
            width: modsList.width
            height: 18

            Row {
                width: parent.width
                height: 16
                spacing: 2

                // Название мода
                Rectangle {
                    width: 200
                    height: 16
                    color: "transparent"

                    Text {
                        text: modelData.name
                        color: "white"
                        font.pixelSize: 8
                        anchors {
                            left: parent.left
                            leftMargin: 2
                            verticalCenter: parent.verticalCenter
                        }
                        elide: Text.ElideRight
                    }
                }

                // Колонка со стрелками
                Column {
                    width: 25
                    height: 16
                    spacing: 1

                    Rectangle {
                        width: 23
                        height: 7
                        color: index > 0 ? "#404040" : "#202020"
                        border.width: 1
                        border.color: "#606060"

                        Text {
                            text: "▲"
                            color: index > 0 ? "white" : "#606060"
                            font.pixelSize: 6
                            anchors.centerIn: parent
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: ctrl.moveUp(index)
                        }
                    }

                    Rectangle {
                        width: 23
                        height: 7
                        color: index < modsList.count - 1 ? "#404040" : "#202020"
                        border.width: 1
                        border.color: "#606060"

                        Text {
                            text: "▼"
                            color: index < modsList.count - 1 ? "white" : "#606060"
                            font.pixelSize: 6
                            anchors.centerIn: parent
                        }
                    }
                }

                // Колонка Yes/No
                Rectangle {
                    width: 60
                    height: 16
                    color: modelData.enabled ? "#2a6b2a" : "#6b2a2a"
                    border.width: 1
                    border.color: "green"

                    Text {
                        text: modelData.enabled ? "YES" : "NO"
                        color: "white"
                        font.pixelSize: 8
                        anchors.centerIn: parent
                    }
                }
            }
        }
    }

    // ========== КНОПКИ ВНИЗУ ==========
    Row {
        id: buttonsRow
        anchors {
            bottom: parent.bottom
            bottomMargin: 8
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 8

        XC.Button {
            width: 100
            text: "OK"
        }

        XC.Button {
            width: 100
            text: "OPEN MODS FOLDER"
        }

        XC.Button {
            width: 100
            text: "CANCEL"
        }
    }

    // ========== TOOLTIP ==========
    Rectangle {
        width: 305
        height: 25
        anchors {
            bottom: buttonsRow.top
            bottomMargin: 4
            left: parent.left
            leftMargin: 8
        }
        color: "#202020"
        border.width: 1
        border.color: "#404040"
        visible: tooltipText !== ""

        Text {
            id: tooltipText
            text: ""
            color: "#cccc66"
            font.pixelSize: 8
            wrapMode: Text.WordWrap
            anchors {
                fill: parent
                margins: 2
            }
        }
    }
}
