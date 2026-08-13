import QtQuick
import OpenXcom.Controls 1.0 as XC
import OpenXcom 1.0

XC.Popup {
    width:  192
    height: 160
    bgImage.source: "image://xcom/Interface/soldierArmor#PAL_BATTLESCAPE"
    required property Base base
    required property Soldier soldier

    ListModel {
        id: armors
    }

    Item {
        anchors{
            fill: parent
            margins: 2
        }
        Text {
            id: caption
            anchors.horizontalCenter: parent.horizontalCenter
            font{
                pixelSize: 10
                bold: true
            }
            color: "white"
            text: Game.language.get("STR_SELECT_ARMOR_FOR_SOLDIER")
        }

        ListView {
            id: armorsList
            anchors {
                top: caption.bottom
                bottom: cancelBtn.top
                left: parent.left
                right: parent.right
                margins: 2
            }
            delegate:  Text {
                font.pixelSize: 8
                color: "#FFFFFF"
                text: Game.language.get(type) + ':' + count
            }
        }

        XC.Button {
            id: cancelBtn
            width:  140
            height: 16
            text: Game.language.get("STR_CANCEL_UC")
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
            }
        }
    }

    Component.onCompleted: {

        for (let a of Game.mod.armorsForSoldiers)
        {
            if(a)
            {
                if (Game.savedGame.isResearched(a.getRequiredResearch()) &&
                    a.getCanBeUsedBy(soldier))
                {
                    if (a.hasInfiniteSupply())
                    {
                        armors.append({"type": a.type, "count": -1 })
                    }
                    else
                    {
                        let armorsOnBase = base.storage.countOf(a.getStoreItem())
                        if (armorsOnBase > 0 || a.getStoreItem() === soldier.armor.getStoreItem())
                        {
                            armors.append({"type": a.type, "count": armorsOnBase})
                        }
                    }
                }
            }
        }

        armorsList.model = armors

    }
}
