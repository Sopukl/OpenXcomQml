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
                model: [{text: "640x480",   value: Qt.size(640,480)},
                        {text: "800x600",   value: Qt.size(800,600)},
                        {text: "1024x768",  value: Qt.size(1024,768)},
                        {text: "1280x1024", value: Qt.size(1280,1024)}]

                Component.onCompleted: {
                    let cur = Qt.size(Options1.displayWidth,
                                      Options1.displayHeight);

                    currentIndex = model.findIndex(e=>e.value === cur)
                }
                onCurrentIndexChanged: {
                    let oldVal = Qt.size(Options1.displayWidth,
                                         Options1.displayHeight)
                    let curVal = model[currentIndex].value

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
                model: [{text: "1x",  value: 1},
                        {text: "2x",  value: 2},
                        {text: "3x",  value: 3},
                        {text: "4x",  value: 4},
                        {text: "5x",  value: 5},
                        {text: "6x",  value: 6},
                        {text: "7x",  value: 7},
                        {text: "8x",  value: 8},
                        {text: "9x",  value: 9},
                        {text: "10x", value: 10}]
                Component.onCompleted: {
                    currentIndex = model.findIndex(
                        e=>e.value === Options1.geoscapeScale)
                }
                onCurrentIndexChanged: Options1.geoscapeScale = model[currentIndex].value
            }
        }
        XC.GroupBox {
            title: "Battlescape scale"
            width: 110
            XC.ComboBox {
                width: parent.width
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
            title: "Display resolution"
            width: 110
            CheckBox {
                text: qsTr("E-mail")
                width: parent.width
            }
        }
        XC.GroupBox {
            title: "Display language"
            width: 110
            XC.ComboBox {
                width: parent.width
            }
        }
        XC.GroupBox {
            title: "Geoscape scale"
            width: 110
            XC.ComboBox {
                width: parent.width
            }
        }
        XC.GroupBox {
            title: "Battlescape scale"
            width: 110
            XC.ComboBox {
                width: parent.width
            }
        }
    }
}
