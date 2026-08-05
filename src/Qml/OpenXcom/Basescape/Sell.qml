import QtQuick
import OpenXcom 1.0
import "../Controls" as XC

XC.Popup {
    id: popup
    width: 320
    height: 200
    required property Base base
    bgImage.source: "image://xcom/fundingWindow"
    component HeaderText: Text {
        font{
            pixelSize: 9
            bold: true
        }
        color: "blue"
        width: contentWidth
    }
    component ValueText: Text {
        color: "white"
        font.pixelSize: 8
    }
    component ListHeaderText: Text {
        height: 9
        font.pixelSize: 9
        color: "white"
    }

    Item {
        anchors{
            fill: parent
            margins: 2
        }
        Text {
            id: caption
            anchors.horizontalCenter: parent.horizontalCenter
            text: Game.language.get("STR_SELL_ITEMS_SACK_PERSONNEL")
            font{
                pixelSize: 12
                bold: true
            }
            color: "blue"
        }
        Item {
            id: summaryInfo
            anchors{
                top: caption.bottom
                topMargin: 2
                left: parent.left
                right: parent.right
            }
            height: 18
            HeaderText {
                id: txtValOfSales
                text: Game.language.get("STR_VALUE_OF_SALES")
            }
            ValueText {
                id: txtFundsOfSales
                anchors {
                    left: txtValOfSales.right
                    right: parent.horizontalCenter
                    rightMargin: 1
                }
                text: "$90210"
            }

            HeaderText {
                id: txtFunds
                anchors {
                    left: parent.horizontalCenter
                }
                text: Game.language.get("STR_FUNDS")
            }
            ValueText {
                id: txtFundsVal
                anchors {
                    left: txtFunds.right
                    right: parent.right
                    rightMargin: 1
                }
                text: "$12390210"
            }
            HeaderText {
                id: txtSpace
                anchors {
                    top: txtFunds.bottom
                    left: parent.horizontalCenter
                }
                text: Game.language.get("STR_SPACE_USED")
            }
            ValueText {
                id: txtSpaceVal
                anchors {
                    top: txtSpace.top
                    left: txtSpace.right
                    right: parent.right
                    rightMargin: 1
                }
                text: "45.6"
            }
        }
        Item {
            id: listHeader
            anchors{
                top: summaryInfo.bottom
                topMargin: -2
                left: summaryInfo.left
                right: summaryInfo.right
            }
            height: 14
            XC.ComboBox {
                id: cbxCategory
                width: 120
                height: 18
                anchors.bottom: parent.bottom

                function formatText(index) {
                    return Game.language.get(model[index])
                }

                model: {
                    let res = []

                    res.push("STR_ALL_ITEMS");
                    res.push("STR_FILTER_HIDDEN");

                    if (Options1.oxceBaseFilterResearchable)
                    {
                        res.push("STR_FILTER_RESEARCHED");
                        res.push("STR_FILTER_RESEARCHABLE");
                    }
                    return res;
                }

                currentIndex: 0
                onActivated: {}

            }
            ListHeaderText {
                id: txtQuantity
                width: 54
                anchors{
                    bottom: parent.bottom
                    left: cbxCategory.right
                    leftMargin: 1
                }
                text: Game.language.get("STR_QUANTITY_UC")
            }
            ListHeaderText {
                id: txtCount
                width: 96
                anchors{
                    bottom: parent.bottom
                    left: txtQuantity.right
                    leftMargin: 1
                }
                text: Game.language.get("STR_SELL_SACK")
            }
            ListHeaderText {
                id: txtPrice
                width: 54
                anchors{
                    bottom: parent.bottom
                    left: txtCount.right
                    leftMargin: 1
                }
                text: Game.language.get("STR_VALUE")
            }
        }


        XC.Button {
            id: sellBtn
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.horizontalCenter
                rightMargin: 2
            }
            text: Game.language.get("STR_SELL_SACK")
        }
        XC.Button {
            id: cancelBtn
            anchors{
                bottom: parent.bottom
                right: parent.right
                left: parent.horizontalCenter
                leftMargin: 2
            }
            text: Game.language.get("STR_CANCEL")
        }
    }

    Shortcut {
        sequence: "Q"
        onActivated: {
            console.log(base.soldiers)
            for(let s of base.soldiers)
                console.log(s.name + ':' + s.craft)
        }
    }
}
