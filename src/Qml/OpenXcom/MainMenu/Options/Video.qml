import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC
import "." as This
This.Page {
    title: "Video"
    Column
    {
        x: 2
        spacing: 2
        XC.GroupBox {
            title: "Display resolution"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [Qt.size(640,480),
                        Qt.size(800,600),
                        Qt.size(1024,768),
                        Qt.size(1280,1024)]

                function formatText(index) {
                    return model[index].width+'x'+model[index].height;
                }

                Component.onCompleted: {
                    let cur = Qt.size(Options1.displayWidth,
                                      Options1.displayHeight);

                    currentIndex = model.findIndex(e=>e === cur)
                }

                onActivated: {
                    let oldVal = Qt.size(Options1.displayWidth,
                                         Options1.displayHeight)
                    let curVal = model[currentIndex]

                    if(curVal !== oldVal)
                    {
                        Options1.displayWidth  = curVal.width;
                        Options1.displayHeight = curVal.height;
                    }
                }
            }
        }
        XC.GroupBox {
            title: "Display language"
            width: 110
            XC.ComboBox {
                width: parent.width
                textRole: "text"
                model: Game.getLanguages()
                onModelChanged: {
                    currentIndex = model.findIndex(
                        e=>e.value === Options1.language)
                }
                onCurrentIndexChanged: Options1.language = model[currentIndex].value
            }
        }
        XC.GroupBox {
            title: "Geoscape scale"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

                function formatText(index) {
                    return model[index]+'x'
                }

                currentIndex: model.findIndex(e=>e === Options1.geoscapeScale)
                onActivated: Options1.geoscapeScale = model[currentIndex]
            }
        }
        XC.GroupBox {
            title: "Battlescape scale"
            width: 110
            XC.ComboBox {
                width: parent.width
                model: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

                function formatText(index) {
                    return model[index]+'x'
                }

                currentIndex: model.findIndex(e=>e === Options1.battlescapeScale)
                onActivated: Options1.battlescapeScale = model[currentIndex]

            }
        }
    }
    Column
    {
        anchors{
            right: parent.right
            rightMargin: 2
        }
        spacing: 2
        XC.GroupBox {
            title: "Display mode"
            width: 110
            XC.CheckBox {
                text: "FullScreen"
                width: parent.width
                checked: Options1.fullscreen
                onClicked: Options1.fullscreen = checked
            }
        }
        XC.GroupBox {
            title: "Display mode"
            width: 110
            XC.CheckBox {
                text: "Borderless"
                width: parent.width
                checked: Options1.borderless
                onClicked: Options1.borderless = checked
            }
        }
    }
}
