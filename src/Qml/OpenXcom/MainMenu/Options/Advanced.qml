import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC
import "./Advanced" as Advanced
Page {
    title: "Advanced"
    background: null
    TabBar {
        id: tabs
        width: parent.width
        background: null

        Repeater{
            model: ["OXC", "OXCE"]
            delegate: TabButton {
                text: modelData
                onClicked: pages.currentIndex = index
                font.pixelSize: 8
                implicitHeight: 18
                padding: 0
                background: null

                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    color: (index === tabs.currentIndex)?"yellow":"white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

        }
        currentIndex: pages.currentIndex
    }
    SwipeView {
        id: pages
        clip: true
        anchors{
            top: tabs.bottom
            bottom: parent.bottom
            left: parent.left
            right: pagesScroll.left
        }
        Advanced.OXC{}
        Advanced.OXCE{}
    }
    ScrollBar {
        id: pagesScroll
        anchors{
            top: tabs.bottom
            bottom: parent.bottom
            right: parent.right
        }

        property Flickable flickable: pages.currentItem
        policy: ScrollBar.AlwaysOn
        width: 10
        height: parent.height
        size: flickable.visibleArea.heightRatio
        position: flickable.visibleArea.yPosition
        onPositionChanged: {
            if(pressed)
                flickable.contentY = position * (flickable.contentHeight)
        }
    }
}
