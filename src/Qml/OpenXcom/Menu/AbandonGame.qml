import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.Menu.Controls 1.0 as XC

XC.Popup {
    id: popup
    width: 216
    height: 160
    property int origin
    Item {
        anchors{
            fill: parent
            margins: 2
        }
        Text {
            anchors.centerIn: parent
            font.pixelSize: 12
            color: "white"
            text: Game.language.get("STR_ABANDON_GAME_QUESTION");
        }
        XC.Button {
            anchors {
                left: parent.left
                bottom: parent.bottom
                right: parent.horizontalCenter
                rightMargin: 1
            }
            text: Game.language.get("STR_YES");
            onClicked: {
                Game.abandonGame()
                popup.close();
            }
        }
        XC.Button {
            anchors {
                left: parent.horizontalCenter
                leftMargin: 1
                bottom: parent.bottom
                right: parent.right
            }
            text: Game.language.get("STR_NO");
            onClicked: popup.close()
        }
    }
}
