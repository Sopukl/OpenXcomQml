import QtQuick
import QtQuick.Controls
import QtQuick.Window
import OpenXcom 1.0
import OpenXcom.MainMenu 1.0 as Main

Window {
    minimumWidth: Options1.displayWidth
    minimumHeight: Options1.displayHeight
    maximumWidth: Options1.displayWidth
    maximumHeight: Options1.displayHeight
    visible: true
    title: "OpenXcom"

    GameRenderer {
        id: gameWindow
        anchors.fill: parent
        focus: true
        activeFocusOnTab: true
    }

    Main.Menu {
        id: mainMenu
        anchors.centerIn: parent
    }

    Button {
        anchors {
            top: parent.top
            topMargin: 10
            right: parent.right
            rightMargin: 10
        }
        width: 30
        height: 30
        onClicked: mainMenu.visible = !mainMenu.visible
    }
}
