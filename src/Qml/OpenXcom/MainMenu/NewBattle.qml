import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import "./Controls" as Ctrls

Popup {
    id: popup
    anchors.centerIn: parent
    width: 320
    height: 200
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Item {
        width: 320
        height: 200
        anchors.centerIn: parent
        scale: Options1.interfaceScale
        clip: true
        Image {
            width: 320
            height: 200
            source: "image://xcom/mainMenu"
        }
        Text {
            id: caption
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 12
            text: "MISSION GENERATOR"
            color: "white"
        }

        Column {
            width: 310
            height: contentHeight
            spacing: 2
            anchors{
                top: caption.bottom
                topMargin: 2
                horizontalCenter: parent.horizontalCenter
            }
            Item {
                width: 310
                height: 16
                Text {
                    //mission
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }
                    font.pixelSize: 8
                    text: "MISSION"
                    color: "white"
                }
                Ctrls.ComboBox {
                    id: customCombo
                    width: 200
                    height: 16
                    model: ["one","two", "three"]
                    currentIndex: 0
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                }
            }
            Item {
                width: 310
                height: 16
                Text {
                    //craft
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                    }
                    font.pixelSize: 8
                    text: "CRAFT"
                    color: "white"
                }
                Rectangle {
                    width: 200
                    height: 16
                    color: "blue"
                    anchors{
                        verticalCenter: parent.verticalCenter
                        right: parent.right
                    }
                }
            }

        }

        Rectangle {
            anchors.fill: parent
            color: "#00000000"
            border {
                width: 1
                color: "green"
            }
        }
    }

 //    // Create objects
    // _btnQuickSearch = new TextEdit(this, 48, 9, 264, 183);
    // _txtTitle = new Text(304, 17, 8, 9);

    // _txtMapOptions = new Text(148, 9, 8, 68);
    // _frameLeft = new Frame(148, 96, 8, 78);
    // _txtAlienOptions = new Text(148, 9, 164, 68);
    // _frameRight = new Frame(148, 96, 164, 78);

    // _btnUfoLanded = new ToggleTextButton(100, 16, 212, 8);

    // _txtMission = new Text(100, 9, 8, 30);
    // _cbxMission = new ComboBox(this, 214, 16, 98, 26);
    // _btnMission = new TextButton(16, 16, 81, 26);

    // _txtCraft = new Text(100, 9, 8, 50);
    // _cbxCraft = new ComboBox(this, 106, 16, 98, 46);
    // _btnEquip = new TextButton(106, 16, 206, 46);

    // _txtDarkness = new Text(120, 9, 22, 83);
    // _slrDarkness = new Slider(120, 16, 22, 93);

    // _txtTerrain = new Text(120, 9, 22, 113);
    // _cbxTerrain = new ComboBox(this, 120, 16, 22+9, 123);
    // _btnTerrain = new TextButton(16, 16, 5+9, 123);

    // _txtDepth = new Text(120, 9, 22, 143);
    // _slrDepth = new Slider(120, 16, 22, 153);

    // _txtGlobeTexture = new Text(120, 9, 22, 143);
    // _btnGlobeTexture = new TextButton(120, 16, 22, 153);
    // _btnGlobeTextureToggle = new TextButton(16, 16, 145, 153);

    // _txtDifficulty = new Text(120, 9, 178, 83);
    // _cbxDifficulty = new ComboBox(this, 120, 16, 178, 93);

    // _txtAlienRace = new Text(120, 9, 178, 113);
    // _cbxAlienRace = new ComboBox(this, 120, 16, 178+9, 123);
    // _btnAlienRace = new TextButton(16, 16, 161+9, 123);

    // _txtAlienTech = new Text(120, 9, 178, 143);
    // _slrAlienTech = new Slider(120, 16, 178, 153);

    // _btnOk = new TextButton(100, 16, 8, 176);
    // _btnCancel = new TextButton(100, 16, 110, 176);
    // _btnRandom = new TextButton(100, 16, 212, 176);

    // _lstSelect = new TextList(288, 144, 8, 28);
    onClosed: destroy()
}
