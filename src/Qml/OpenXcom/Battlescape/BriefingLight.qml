import QtQuick
import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.Popup {
    width:  320
    height: 200
    required property AlienDeployment alienDeployment

    bgImage.source: {
        let briefingData = alienDeployment.briefingData;
        let background = briefingData.background
        let paletteOffset = briefingData.paletteOffset

        return `image://xcom/${background}#PAL_GEOSCAPE:${paletteOffset}`
    }
}
