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
                model: ["One", "Two", "Three"]
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
