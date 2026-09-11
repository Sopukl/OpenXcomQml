import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Dialog {
    id: popup
    anchors.centerIn: parent
    width: 320
    height: 200

    Text {
        id: caption
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 12
        text: "MISSION GENERATOR"
        color: "white"
    }
    Column {
        width: 310
        height: contentHeight
        spacing: 2
        anchors{
            top: caption.bottom
            topMargin: 2
            horizontalCenter: parent.horizontalCenter
        }
        Item {
            width: 310
            height: 18
            Text {
                //mission
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                font.pixelSize: 8
                text: "MISSION"
                color: "white"
            }
            XC.ComboBox {
                id: customCombo
                width: 200
                model: ["one","two", "three"]
                currentIndex: 0
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                }
            }
        }
        Item {
            width: 310
            height: 18
            Text {
                //craft
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                font.pixelSize: 8
                text: "CRAFT"
                color: "white"
            }
            XC.ComboBox {
                id: customCombo1
                width: 99
                model: ["one","two", "three"]
                currentIndex: 0
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: customCombo2.left
                    rightMargin: 2
                }
            }
            XC.Button {
                id: customCombo2
                width: 99
                text: "Craft"
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                }
            }
        }
    }
    Item {
        width: parent.width
        height: contentHeight
        Text {
            id: txtMapOptions
            text: "MAP OPTIONS"
            width: 148
            height: 9
            x: 5
            y: 70
            font.pixelSize: 8
            color: "white"
        }
        Rectangle {
            width: 148
            height: 96
            x: 5
            y: 80
            color: "#00000000"
            border {
                width: 1
                color: "green"
            }
        }

        Text {
            id: txtAlienOptions
            text: "ALIEN OPTIONS"
            width: 148
            height: 9
            y: 70
            anchors{
                right: parent.right
                rightMargin: 5
            }
            font.pixelSize: 8
            color: "white"
        }
        Rectangle {
            width: 148
            height: 96
            y: 80
            anchors{
                right: parent.right
                rightMargin: 5
            }
            color: "#00000000"
            border {
                width: 1
                color: "green"
            }
        }
    }
}
