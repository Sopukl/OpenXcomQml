import QtQuick
import QtQuick.Controls
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC
import "./Options" as Pages

XC.Popup {
    width: 320
    height: 200

    ListView {
        id: pagesList
        anchors {
            top: parent.top
            topMargin: 2
            bottom: btns.top
            bottomMargin: 2
        }

        x: 2
        y: 2
        width: 80
        currentIndex: pages.currentIndex
        model: pages.count
        spacing: 2
        delegate: XC.Button {
            width: pagesList.width
            text: pages.itemAt(index).title
            onClicked: {
                pages.currentIndex = index
            }
        }
    }
    SwipeView {
        id: pages
        anchors {
            top: parent.top
            topMargin: 2
            bottom: btns.top
            bottomMargin: 2
        }
        x: 84
        spacing: 2
        width: 234
        background: null
        orientation: Qt.Vertical
        clip: true
        Pages.Video {}
        Pages.Audio {
        }
        Pages.Page {
            title: "Controls"
        }
        Pages.Page {
            title: "Geoscape"
        }
        Pages.Page {
            title: "Battlescape"
        }
        Pages.Page {
            title: "Advanced"
        }
        Pages.Page {
            title: "Folders"
        }
    }
    Row {
        id: btns
        anchors{
            bottom: parent.bottom
            bottomMargin: 2
            horizontalCenter: parent.horizontalCenter
        }
        spacing: 2
        XC.Button {
            text: "Ok"
            width: 104
            onClicked: {
                Options1.saveSettings();
                close();
            }
        }
        XC.Button {
            text: "Cancel"
            width: 104
            onClicked: close();
        }
        XC.Button {
            text: "Restore defaults"
            width: 104
        }
    }


    //    _window = new Window(this, 320, 200, 0, 0);

    // _btnVideo = new TextButton(80, 16, 8, 8);
    // _btnAudio = new TextButton(80, 16, 8, 28);
    // _btnControls = new TextButton(80, 16, 8, 48);
    // _btnGeoscape = new TextButton(80, 16, 8, 68);
    // _btnBattlescape = new TextButton(80, 16, 8, 88);
    // _btnAdvanced = new TextButton(80, 16, 8, 108);
    // _btnFolders = new TextButton(80, 16, 8, 128);

    // _btnOk = new TextButton(100, 16, 8, 176);
    // _btnCancel = new TextButton(100, 16, 110, 176);
    // _btnDefault = new TextButton(100, 16, 212, 176);

    // _txtTooltip = new Text(305, 25, 8, 148);

}
