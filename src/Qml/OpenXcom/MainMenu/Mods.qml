import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC

XC.Popup {
    id: ctrl
    width: 320
    height: 200
    anchors.centerIn: parent
    property var mods: Game.getModsInfo()

    function moveUp(idx) {
        if(idx > 0)
        {
            [mods[idx-1], mods[idx]] = [mods[idx], mods[idx-1]];
            modsChanged();
        }
    }
    function moveMod(idxFrom, idxTo) {
        [mods[idxFrom], mods[idxTo]] = [mods[idxTo], mods[idxFrom]];
        modsChanged();
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

        displayText: mods[currentValue]?.name??"undefined"
        function formatText(index) {
            return mods[model[index]].name??"undefined"
        }

        model: {
            let res = []
            for(let idx in mods)
                if(mods[idx].isMaster)
                    res.push(idx)
            return res
        }
        onModelChanged: currentIndex= model.findIndex(e=>mods[e].enabled)
        onActivated: {
            for(let idx in model)
                model[idx].enabled = (idx === currentIndex)
        }
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
            let res = []
            let masterMod = mods[masterCombo.currentValue]
            for(let idx in mods)
                if(!mods[idx].isMaster &&
                   (mods[idx].masterId === masterMod.id))
                    res.push(idx)
            return res;
        }

        delegate: Item {
            id: delegateItem
            width: modsList.width
            height: 10
            Row {
                id: rrow
                width: parent.width
                height: parent.height
                spacing: 2

                // Название мода
                Rectangle {
                    width: 200
                    height: 10
                    color: "transparent"

                    Text {
                        text: mods[modelData].name
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
                    height: 10

                    Rectangle {
                        width: 23
                        height: 4
                        enabled: index > 0
                        color: enabled ? "#404040" : "#202020"
                        border.width: 1
                        border.color: "#606060"

                        Text {
                            text: "▲"
                            color: enabled ? "white" : "#606060"
                            font.pixelSize: 4
                            anchors.centerIn: parent
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: ctrl.moveMod(modsList.model[index],
                                                    modsList.model[index-1])
                        }
                    }

                    Rectangle {
                        width: 23
                        height: 4
                        enabled: index < modsList.count - 1
                        color: enabled ? "#404040" : "#202020"
                        border.width: 1
                        border.color: "#606060"

                        Text {
                            text: "▼"
                            color: enabled ? "white" : "#606060"
                            font.pixelSize: 4
                            anchors.centerIn: parent
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: ctrl.moveMod(modsList.model[index],
                                                    modsList.model[index+1])
                        }

                    }
                }

                // Колонка Yes/No
                Rectangle {
                    width: 60
                    height: 10
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
