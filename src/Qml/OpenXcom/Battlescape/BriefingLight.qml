import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Popup {
    width:  320
    height: 200
    required property AlienDeployment alienDeployment
    property RuleStartingCondition startingCondition: Game.mod.startingCondition(alienDeployment.startingCondition)

    bgImage.source: {
        let briefingData = alienDeployment.briefingData;
        let background = briefingData.background
        let paletteOffset = briefingData.paletteOffset

        return `image://xcom/${background}#PAL_GEOSCAPE:${paletteOffset}`
    }

    component ConditionEntryText: Text {
        font.pixelSize: 8
        elide: Text.ElideRight
        color: "#00CDBD"
    }
    component ConditionEntryList: Column {
        id: cEntryList
        width: armorsList.width/2
        spacing: 1
        property alias model: cRep.model
        Repeater {
            id: cRep
            delegate: ConditionEntryText {
                width: cEntryList.width
                height: 10
                text: Game.language.get(modelData)
            }
        }
    }

    Item {
        anchors{
            fill: parent
            margins: 2
        }

        Text {
            id: title
            height: 32
            anchors{
                left: parent.left
                right: parent.right
                top: parent.top
                topMargin: 8
            }
            font.pixelSize: 12
            color: "#00CDBD"
            wrapMode: Text.WordWrap
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
            text: Game.language.get(alienDeployment.type)
        }

        Text {
            id: briefing
            anchors{
                left: parent.left
                right: parent.right
                top: title.bottom
                topMargin: 4
                bottom: showArmorsBtn.top
                bottomMargin: 2
            }
            font.pixelSize: 8
            color: "#00CDBD"
            wrapMode: Text.WordWrap
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
            text: Game.language.get(alienDeployment.alertDescription)
        }

        Text {
            id: armorsListTitle
            anchors{
                left: parent.left
                bottom: title.bottom
            }
            font.pixelSize: 8
            color: "#00CDBD"
            wrapMode: Text.WordWrap
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
            visible: armorsList.visible
        }

        Flickable {
            id: armorsList
            anchors{
                left: parent.left
                right: parent.right
                top: title.bottom
                bottom: showArmorsBtn.top
                bottomMargin: 2
            }
            clip: true
            flickableDirection: Flickable.VerticalFlick
            contentWidth: rrr.width
            contentHeight: rrr.height
            visible: !briefing.visible

            Row {
                id: rrr
                ConditionEntryList {
                    id: col1
                }
                ConditionEntryList {
                    id: col2
                }
            }
        }

        XC.Button {
            id: showArmorsBtn
            anchors {
                bottom: parent.bottom
                left: parent.left
                right: parent.horizontalCenter
                rightMargin: 1
            }
            text: Game.language.get("STR_WHAT_CAN_I_WEAR")
            onClicked: briefing.visible = !briefing.visible
            visible: false
        }
        XC.Button {
            id: okBtn
            anchors {
                bottom: parent.bottom
                left: parent.horizontalCenter
                leftMargin: 1
                right: parent.right
            }
            text: Game.language.get("STR_OK")
            onClicked: close()
        }
    }
    Component.onCompleted: {
        function splitStringList(stringsList)
        {
            const mid = Math.ceil(stringsList.length / 2)
            col1.model = stringsList.slice(0, mid);
            col2.model = stringsList.slice(mid);
        }
        if(startingCondition)
        {
            if(startingCondition.allowedArmors.length > 0)
            {
                splitStringList(startingCondition.allowedArmors)
                armorsListTitle.text = Game.language.get("STR_STARTING_CONDITION_ARMORS_ALLOWED")
                showArmorsBtn.visible = true
            }
            else
            if(startingCondition.forbiddenArmors.length > 0)
            {
                splitStringList(startingCondition.forbiddenArmors)
                armorsListTitle.text = Game.language.get("STR_STARTING_CONDITION_ARMORS_FORBIDDEN")
                showArmorsBtn.visible = true
            }
        }
    }
}
