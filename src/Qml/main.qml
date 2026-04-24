import QtQuick
import QtQuick.Controls
import QtQuick.Window
import OpenXcom 1.0
import OpenXcom.MainMenu 1.0 as Main

Window {
    id: wnd
    minimumWidth:  Options1.displayWidth
    minimumHeight: Options1.displayHeight

    maximumWidth:  Options1.fullscreen?1000000:
                                       Options1.displayWidth

    maximumHeight: Options1.fullscreen?1000000:
                                       Options1.displayHeight

    visibility: Options1.fullscreen?Window.FullScreen:
                                    Window.Windowed

    flags: Options1.borderless?Qt.FramelessWindowHint:
                               Qt.Window

    onVisibilityChanged: {
        if(visibility === Window.Windowed)
        {
            wnd.x = 50
            wnd.y = 50
        }
    }

    visible: true
    title: "OpenXcom"
    color: "#000000"
    property real eScale: {
        let wScale = wnd.width/root.width
        let hScale = wnd.height/root.height
        return Math.min(wScale, Math.min(hScale, Options1.geoscapeScale))
    }

    onEScaleChanged: Options1.interfaceScale = eScale

    GameRenderer {
        id: gameWindow
        anchors.fill: parent
        focus: true
    }

    Loader {
        id: root
        anchors.centerIn: parent
        width: 320
        height: 240

        source: {
            if(Game.state === Game.STARTING)
                return "LoadingFrame.qml"
            if(Game.state === Game.MENU)
                return "GameFrame.qml"
            return ""
        }
        scale: Options1.interfaceScale
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
            root.visible = !root.visible
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
