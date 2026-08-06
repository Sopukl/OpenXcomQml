import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

Control {
    id: ctrl

    required property string key

    implicitWidth: parent?.width??100
    implicitHeight: 18
    font.pixelSize: 10
    opacity: enabled ? 1.0 : 0.3

    property alias text: caption.text
    property int hOrientation: Qt.RightToLeft
    property int min: 1
    property int max: 10
    property int step: 1
    property int current: Options1[key]
    padding: 2

    contentItem: Item {
        Rectangle {
            id: input
            width: ctrl.height
            height: ctrl.height
            border.color: "#21be2b"
            color: "#00000000"
            anchors {
                left:  hOrientation === Qt.LeftToRight?parent.left:undefined
                right: hOrientation === Qt.RightToLeft?parent.right:undefined
                verticalCenter: parent.verticalCenter
            }

            Text {
                anchors.fill: parent
                font: ctrl.font
                color: "#21be2b"
                text: current
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: (mouse)=> {
                    let newVal = (mouse.button === Qt.LeftButton)?
                            current + step:
                            current - step;

                    Options1[key] = (newVal > max)?min:
                                    (newVal < min)?max:
                                     newVal;
                }
            }
        }

        Text {
            id: caption
            text: ctrl.text
            font: ctrl.font
            color: "#21be2b"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideRight
            anchors {
                left:  hOrientation === Qt.LeftToRight?input.right:parent.left
                leftMargin: hOrientation === Qt.LeftToRight?2:0
                right: hOrientation === Qt.RightToLeft?input.left:parent.right
                rightMargin: hOrientation === Qt.RightToLeft?2:0
                verticalCenter: parent.verticalCenter
            }
        }
    }
}
