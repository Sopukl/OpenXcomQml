import QtQuick 2.15
import OpenXcom 1.0

MouseArea {
    anchors.fill: parent
    property GeoscapeState geoscape

    acceptedButtons: Qt.AllButtons
    hoverEnabled: true
    onPositionChanged: geoscape.setBuildNewBasePos(mouseX, mouseY)
    onClicked: (mouse) => {
        if(mouse.button === Qt.RightButton)
            geoscape.globeCenterAt(mouseX, mouseY)
        else
        if(mouse.button === Qt.RightButton)
            geoscape.globeCenterAt(mouseX, mouseY)
    }

    Component.onCompleted: forceActiveFocus()
}
