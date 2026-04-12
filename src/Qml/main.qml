import QtQuick
import QtQuick.Controls
import QtQuick.Window
import OpenXcom 1.0
import OpenXcom.MainMenu 1.0 as Main

Window {
    id: wnd
    minimumWidth: Options1.displayWidth
    minimumHeight: Options1.displayHeight
    maximumWidth: Options1.displayWidth
    maximumHeight: Options1.displayHeight
    visible: true
    title: "OpenXcom"
    property real tScale: 1.0
    property real eScale: {
        let wScale = wnd.width/root.width
        let hScale = wnd.height/root.height
        return Math.min(wScale, Math.min(hScale, tScale))
    }

    GameRenderer {
        id: gameWindow
        anchors.fill: parent
        focus: true
    }

    Item {
        id: root
        anchors.centerIn: parent
        width: 320
        height: 240

        Main.StartingFrame {
            anchors.centerIn: parent
            visible: Game.state === Game.STARTING
        }

        Main.Menu {
            id: mainMenu
            anchors.centerIn: parent
            visible: Game.state === Game.MENU
        }

        scale: eScale
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
        onClicked: {
            mainMenu.visible = !mainMenu.visible
        }
    }

    // Slider {
    //     anchors {
    //         horizontalCenter: parent.horizontalCenter
    //         bottom: parent.bottom
    //         bottomMargin: 5
    //     }
    //     from: 0.5
    //     to: 4.0
    //     stepSize: 0.5
    //     value: wnd.tScale
    //     onValueChanged: wnd.tScale = value
    // }
}
