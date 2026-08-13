import QtQuick 2.15

Popup {
    id: ctrl
    width: 256
    height: 160
    required property string errorText
    bgImage.source: "image://xcom/Interface/itemsArriving"

    Text {
        id: q12
        anchors{
            top: parent.top
            bottom: closeBtn.top
            left: parent.left
            right: parent.right
            margins: 2
        }
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 10
        elide: Text.ElideRight
        color: "white"
        text: errorText
    }
    Button {
        id: closeBtn
        anchors{
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 2
        }
        text: "Close"
        onClicked: ctrl.destroy()
    }
}
