import QtQuick
import QtQml.Models
import OpenXcom 1.0
import "../Controls" as XC

XC.Popup {
    id: popup
    width: 320
    height: 200
    required property Base base
    bgImage.source: "image://xcom/fundingWindow"

    Component.onCompleted: {
        console.log("base: " + popup.base )
    }
}
