import QtQuick
import QtQuick.Controls
import QtQuick.Window
import OpenXcom 1.0
import OpenXcom.Menu 1.0 as Main
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
        let wScale = wnd.width/320
        let hScale = wnd.height/240
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

            function onErrorMessage(message) {
                Xcom.createWindow("/OpenXcom/Controls/ErrorMessage.qml",
                                  gameWindow, {"errorText": message}).open()
            }
            function onOpenDialog(url, params = {}) {
                console.log(url + " : " + params)
                Xcom.createWindow(url, gameWindow, params).open()
            }
        }
    }
}
