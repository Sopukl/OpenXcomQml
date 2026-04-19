import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

ComboBox {
    id: ctrl
    implicitWidth: 100
    implicitHeight: 18
    currentIndex: 0
    editable: false
    font.pixelSize: 9
    textRole: "text"
    anchors{
        verticalCenter: parent.verticalCenter
        right: parent.right
    }

    background: Rectangle {
        implicitWidth: 120
        implicitHeight: 40
        border.color: "blue"
        border.width: ctrl.visualFocus ? 2 : 1
    }
    contentItem: Text {
        anchors.fill: parent

        text: ctrl.displayText
        font: ctrl.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideRight
        color: "black"
    }
    indicator: Rectangle {
        id: canvas
        x: ctrl.width - width - ctrl.rightPadding
        y: ctrl.topPadding + (ctrl.availableHeight - height) / 2
        width: 8
        height: 8
        color: "blue"
    }

    delegate: ItemDelegate {
        id: delegate

        required property var model
        required property int index

        width: ctrl.width
        height: ctrl.height
        padding: 0
        contentItem: Text {
            text: delegate.model[ctrl.textRole]
            color: "#21be2b"
            font: ctrl.font
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        highlighted: ctrl.highlightedIndex === index
    }

    popup: Popup {
        width: ctrl.width
        height: Math.min(200, contentHeight)
        padding: 0
        scale: Options1.interfaceScale
        transformOrigin: Item.TopLeft
        property rect cbRect: ctrl.mapToItem(parent, ctrl.x, ctrl.y,
                                             ctrl.width, ctrl.height)

        y: cbRect.y + cbRect.height + 1
        contentItem: ListView
        {
            id: listView
            clip: true
            implicitHeight: contentHeight
            model: ctrl.popup.visible ? ctrl.delegateModel : null
            currentIndex: ctrl.highlightedIndex
        }

        background: Rectangle {
            border.color: "gray"
            border.width: 1
        }
    }
}
