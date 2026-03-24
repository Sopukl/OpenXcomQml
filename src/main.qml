import QtQuick 2.15
import QtQuick.Window 2.15
import OpenXcom 1.0

Window {
    width: 1280
    height: 1024
    visible: true
    title: "OpenXcom"

    GameRenderer {
        id: gameWindow
        anchors.fill: parent
        focus: true
        activeFocusOnTab: true
    }
}
