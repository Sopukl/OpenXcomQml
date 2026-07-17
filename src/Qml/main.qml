import QtQuick
import QtQuick.Controls
import QtQuick.Window
import OpenXcom 1.0
import OpenXcom.MainMenu 1.0 as Main
import "./OpenXcom/Controls" as XC

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
        Connections {
            target: Game
            function onCreateNewBase(geoscape, base, isFirst) {
                Xcom.createWindow("Geoscape/BuildNewBase.qml", gameWindow,
                   {geoscape: geoscape,
                    base: base,
                    isFirst: isFirst})
            }

            function onOpenPopupWindow(path, params) {
                Xcom.createWindow(path, gameWindow, params).open()
            }
            // function onSavedGameChanged() {
            //     console.log(Game.savedGame)
            //     console.log(Game.savedGame.bases)
            //     console.log(Game.savedGame.bases.length)
            // }
        }
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
    XC.Button {
        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 10
        }
        text: "BASE INFO"
        palette.button: "white"
        width: 60
        height: 30
        onClicked: {
            let base = Game.savedGame.bases[0];
            console.log("base: " + base.name)
            console.log("soldiers")
            for(let s of base.soldiers)
                console.log(s.name)

            console.log("crafts")
            for(let c of base.crafts)
                console.log(c.name)
        }
    }

}
