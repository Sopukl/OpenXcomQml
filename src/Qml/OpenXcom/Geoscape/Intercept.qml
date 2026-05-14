import QtQuick
import OpenXcom 1.0
import "../Controls" as XC

XC.Popup {
    width: 320
    height: 140

    bgImage.source: "image://xcom/intercept"

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 10
        text: "LAUNCH INTERCEPTION"
    }
}
