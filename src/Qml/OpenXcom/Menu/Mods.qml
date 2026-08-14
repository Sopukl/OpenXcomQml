import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: ctrl
    width: 320
    height: 200
    anchors.centerIn: parent
    property var mods: Game.getModsInfo()

    ListModel {
        id: modsModel
    }

    function visibleModIndexes() {
        let res = [];
        let masterMod = mods[masterCombo.currentValue];

        if(masterMod === undefined)
            return res;

        mods.forEach((mod, idx) =>
        {
            if(!mod.isMaster &&
               (mod.masterId === masterMod.id))
                res.push(idx);
        })
        return res;
    }

    function rebuildModsModel() {
        modsModel.clear();
        visibleModIndexes().forEach(modIdx =>
        {
            let mod = mods[modIdx];
            modsModel.append({
                "modId": mod.id,
                "modName": mod.name,
                "modEnabled": mod.enabled
            });
        })
    }

    function syncModsFromModel() {
        let visibleMods = visibleModIndexes();
        let modsById = {};

        mods.forEach(mod => modsById[mod.id] = mod);
        visibleMods.forEach((modIdx, idx) => mods[modIdx] = modsById[modsModel.get(idx).modId]);
    }

    function moveMod(fromListIndex, toListIndex) {
        if(fromListIndex === toListIndex ||
           fromListIndex < 0 ||
           toListIndex < 0 ||
           fromListIndex >= modsList.count ||
           toListIndex >= modsList.count)
            return false;

        modsModel.move(fromListIndex, toListIndex, 1);
        syncModsFromModel();
        return true;
    }

    Component.onCompleted: rebuildModsModel()

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
        onCurrentValueChanged: ctrl.rebuildModsModel()
        onActivated: {
            model.forEach((modIdx, idx) =>
                mods[modIdx].enabled = (idx === currentIndex))
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

        model: modsModel

        delegate: Item {
            id: delegateItem
            width: modsList.width
            height: 10
            z: dragArea.drag.active ? 1 : 0

            Item {
                id: dragContent
                width: parent.width
                height: parent.height

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
                            text: modName
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
                    MouseArea {
                        id: dragArea
                        width: 25
                        height: 10
                        Column {
                            id: col
                            anchors.fill: parent
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
                            }
                        }
                        preventStealing: true
                        drag.target: dragContent
                        drag.axis: Drag.YAxis
                        drag.minimumY: -delegateItem.y
                        drag.maximumY: modsList.contentHeight - delegateItem.y - delegateItem.height
                        cursorShape: pressed ? Qt.ClosedHandCursor:
                                               Qt.OpenHandCursor
                        property int fromIndex: -1

                        onPressed: fromIndex = index
                        onPositionChanged: {
                            if(fromIndex >= 0)
                            {
                                let targetIndex = modsList.indexAt(width / 2,
                                    delegateItem.y + dragContent.y + delegateItem.height / 2);

                                if(targetIndex >= 0 &&
                                   targetIndex !== fromIndex &&
                                   ctrl.moveMod(fromIndex, targetIndex))
                                {
                                    fromIndex = targetIndex;
                                    dragContent.y = 0;
                                }
                            }
                        }
                        onReleased: {
                            dragContent.y = 0;
                            fromIndex = -1;
                        }
                        onCanceled: {
                            dragContent.y = 0;
                            fromIndex = -1;
                        }

                    }

                    // Колонка Yes/No
                    Rectangle {
                        width: 60
                        height: 10
                        color: modEnabled ? "#2a6b2a" : "#6b2a2a"
                        border.width: 1
                        border.color: "green"

                        Text {
                            text: modEnabled ? "YES" : "NO"
                            color: "white"
                            font.pixelSize: 8
                            anchors.centerIn: parent
                        }
                    }
                }
            }
        }

        Transition {
            id: tr
            NumberAnimation {
                properties: "y"
                duration: 100
            }
        }

        move: tr
        moveDisplaced: tr
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
            onClicked: {
                Game.setModsInfo(ctrl.mods);
                close();
            }
        }

        XC.Button {
            width: 100
            text: "OPEN MODS FOLDER"
        }

        XC.Button {
            width: 100
            text: "CANCEL"
            onClicked: ctrl.close();
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
