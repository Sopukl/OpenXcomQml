import QtQuick
import QtQuick.Controls
import OpenXcom 1.0

ComboBox {
    id: ctrl
    width: 100
    height: 16
    currentIndex: 0
    editable: false
    anchors{
        verticalCenter: parent.verticalCenter
        right: parent.right
    }
    popup: Popup {
        width: ctrl.width
        height: Math.min(200, contentHeight)
        padding: 0
        scale: Options1.interfaceScale
        transformOrigin: Item.TopLeft
        property rect cbRect: ctrl.mapToItem(parent, ctrl.x, ctrl.y,
                                             ctrl.width, ctrl.height)

        y: cbRect.y + cbRect.height
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
