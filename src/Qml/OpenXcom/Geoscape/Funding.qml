import QtQuick
import OpenXcom 1.0
import "../Controls" as XC

XC.Popup {
    id: popup
    width: 320
    height: 140

    bgImage.source: "image://xcom/fundingWindow"
    ListModel {
        id: mdl
    }

    Text {
        id: caption
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 2
        }
        font{
            pixelSize: 12
            bold: true
        }
        text: "International Relations"
        color: "#64CCBC"

    }

    ListView {
        id: list
        anchors{
            top: caption.bottom
            topMargin: 1
            bottom: okBtn.top
            bottomMargin: 1
            left: parent.left
            leftMargin: 5
            right: parent.right
            rightMargin: 5
        }
        clip: true
        spacing: 2
        delegate: Rectangle {
            width: list.width
            height: 10
            color: "blue"
            Text {
                anchors.centerIn: parent
                font.pixelSize: 9
                color: "white"
                text: name + ':' + funding + ':' + fundingDiff
            }
        }
    }

    XC.Button {
        id: okBtn
        anchors{
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 2
        }
        width: 100
        text: "Ok"
        onClicked: popup.close()
    }
    Component.onCompleted: {
        let _funding = 0;
        let _fundingDiff = 0;
        let l  = 0;
        for(let country of Game.savedGame.countries)
        {
            l = country.funding.length;
            _funding = country.funding[l-1]
            _fundingDiff =  (l > 1)?
                    country.funding[l-1] - country.funding[l-2]:0;

            mdl.append({name: country.name, funding: _funding, fundingDiff: _fundingDiff })
        }
        list.model = mdl
    }
}
