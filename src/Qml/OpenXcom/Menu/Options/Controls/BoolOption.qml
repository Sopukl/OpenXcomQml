import OpenXcom 1.0
import OpenXcom.Controls 1.0 as XC

XC.CheckBox {
    required property string key
    checked: Options1[key]
    onClicked: Options1[key] = !Options1[key]
    hOrientation: Qt.RightToLeft
    padding: 2
    implicitWidth: parent?.width??100
}
