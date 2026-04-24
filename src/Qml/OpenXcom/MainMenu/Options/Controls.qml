import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC
import "." as This
This.Page {
    title: "Controls"
    // Column
    // {
    //     x: 2
    //     spacing: 2
    //     XC.GroupBox {
    //         title: "Scroll Speed"
    //         width: 110
    //         XC.Slider {
    //             width: parent.width
    //             from: 10
    //             to: 100
    //             value: Options1.battleScrollSpeed
    //             onValueChanged: Options1.battleScrollSpeed = value
    //         }
    //     }
    //     XC.GroupBox {
    //         title: "Clock Speed"
    //         width: 110
    //         XC.Slider {
    //             width: parent.width
    //             from: 10
    //             to: 250
    //             value: Options1.geoClockSpeed
    //             onValueChanged: Options1.geoClockSpeed = value
    //         }
    //     }
    //     XC.GroupBox {
    //         title: "Globe Details"
    //         width: 110
    //         ColumnLayout
    //         {
    //             XC.CheckBox {
    //                 width: parent.width
    //                 text: "Countries"
    //                 checked: Options1.globeDetail
    //                 onClicked: Options1.globeDetail = checked
    //             }
    //             XC.CheckBox {
    //                 width: parent.width
    //                 text: "Radars"
    //                 checked: Options1.globeRadarLines
    //                 onClicked: Options1.globeRadarLines = checked
    //             }
    //             XC.CheckBox {
    //                 width: parent.width
    //                 text: "Flight paths"
    //                 checked: Options1.globeFlightPaths
    //                 onClicked: Options1.globeFlightPaths = checked
    //             }
    //         }
    //     }
    // }
    // Column
    // {
    //     anchors{
    //         right: parent.right
    //         rightMargin: 2
    //     }
    //     spacing: 2
    //     XC.GroupBox {
    //         title: "Drag Scroll"
    //         width: 110
    //         XC.ComboBox {
    //             width: parent.width
    //             model: [
    //                 {text: "DISABLED", value: 0},
    //                 {text: "LEFT_MOUSE", value: 1},
    //                 {text: "MIDDLE_MOUSE", value: 2},
    //                 {text: "RIGHT_MOUSE", value: 3},
    //             ]
    //             currentIndex: model.findIndex(
    //                 e=>e.value === Options1.geoDragScrollButton)

    //             onActivated: Options1.geoDragScrollButton = currentValue.value
    //         }
    //     }
    //     XC.GroupBox {
    //         title: "Dogfight Speed"
    //         width: 110
    //         XC.Slider {
    //             width: parent.width
    //             from: 20
    //             to: 50
    //             value: Options1.dogfightSpeed
    //             onValueChanged: Options1.dogfightSpeed = value
    //         }
    //     }
    //     XC.GroupBox {
    //         title: "UI Options"
    //         width: 110
    //         XC.CheckBox {
    //             width: parent.width
    //             text: "Show Funds"
    //             checked: Options1.showFundsOnGeoscape
    //             onClicked: Options1.showFundsOnGeoscape = checked
    //         }
    //     }
    // }
}
