import QtQuick
import QtQml.Models
import OpenXcom 1.0
import "../Controls" as XC

XC.Popup {
    id: popup
    width: 320
    height: 200

    bgImage.source: "image://xcom/fundingWindow"

    readonly property real colNameRatio: 108 / 260
    readonly property real colFundingRatio: 100 / 260
    readonly property real colChangeRatio: 52 / 260

    property string sortColumn: ""
    property int sortOrder: Qt.AscendingOrder
    property int totalFunding: 0

    component HeaderTab: MouseArea {
        height: tableHeader.height
        property string tabName
        property string sortName
        property bool alignLeft:true

        Row {
            anchors {
                left: alignLeft?parent.left:undefined
                right: alignLeft?undefined:parent.right
                leftMargin: 1
                rightMargin: 1
                verticalCenter: parent.verticalCenter
            }
            Text {
                id: caption
                anchors.verticalCenter: parent.verticalCenter
                text: tabName
                font.pixelSize: 8
                color: "#64CCBC"
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 6
                color: "#64CCBC"
                text: sortColumn === sortName ? (sortOrder ? "▲" : "▼") : " "

            }
        }
        onClicked: {
            if (sortColumn === sortName)
            {
                sortOrder = (sortOrder === Qt.AscendingOrder)?
                                Qt.DescendingOrder:
                                Qt.AscendingOrder
            }
            else
            {
                sortColumn = sortName
                sortOrder = true
                sortOrder = Qt.AscendingOrder
            }
        }
        cursorShape: Qt.PointingHandCursor
    }

    SortFilterProxyModel {
        id: fundingProxy
        model: ListModel {}

        sorters: [
            RoleSorter {
                id: nameSorter
                roleName: "name"
                enabled: sortColumn === "name"
                sortOrder: popup.sortOrder
            },
            RoleSorter {
                roleName: "funding"
                enabled: sortColumn === "funding"
                sortOrder: popup.sortOrder
            },
            RoleSorter {
                roleName: "fundingDiff"
                enabled: sortColumn === "fundingDiff"
                sortOrder: popup.sortOrder
            }
        ]
    }

    Text {
        id: caption
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 2
        }
        font {
            pixelSize: 12
            bold: true
        }
        text: "International Relations"
        color: "#64CCBC"
    }

    Row {
        id: tableHeader
        anchors {
            top: caption.bottom
            topMargin: 2
            left: list.left
            right: list.right
        }
        height: 11
        spacing: 0

        HeaderTab {
            width: list.width * colNameRatio
            tabName: "Country"
            sortName: "name"
        }

        HeaderTab {
            width: list.width * colFundingRatio
            tabName: "Funding"
            sortName: "funding"
            alignLeft: false
        }

        HeaderTab {
            width: list.width * colChangeRatio
            tabName: "Change"
            sortName: "fundingDiff"
            alignLeft: false
        }
    }

    ListView {
        id: list
        anchors {
            top: tableHeader.bottom
            topMargin: 1
            bottom: totalFundingLabel.top
            bottomMargin: 1
            left: parent.left
            leftMargin: 5
            right: parent.right
            rightMargin: 5
        }
        clip: true
        spacing: 1
        model: fundingProxy

        highlight: Rectangle {
            width: list.width
            height: 10
            color: "white"
            opacity: 0.2
            y: ListView.view.currentItem.y
        }

        delegate: MouseArea {
            width: list.width
            height: 10
            hoverEnabled: true
            onContainsMouseChanged: {
                if(containsMouse)
                    list.currentIndex = index
            }

            Row {
                width: parent.width
                height: parent.height
                spacing: 0

                Text {
                    width: list.width * colNameRatio
                    height: parent.height
                    text: name
                    font.pixelSize: 8
                    color: "white"
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    width: list.width * colFundingRatio
                    height: parent.height
                    text: {
                        const sign = funding < 0 ? "-" : "";
                        return `${sign}$${Math.abs(funding).toLocaleString()}`;
                    }
                    font.pixelSize: 8
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }

                Text {
                    width: list.width * colChangeRatio
                    height: parent.height
                    text: {
                        const sign = fundingDiff === 0 ? ''  :
                                     fundingDiff < 0   ? "-" : "+";

                        return `${sign}$${Math.abs(fundingDiff).toLocaleString()}`;
                    }

                    font.pixelSize: 8
                    color: "white"
                    horizontalAlignment: Text.AlignRight
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    Text {
        id: totalFundingLabel
        anchors {
            bottom: okBtn.top
            bottomMargin: 2
            left: list.left
            right:list.right
        }

        font.pixelSize: 10
        color: "white"
        text: `TOTAL: ${totalFunding}`

    }

    XC.Button {
        id: okBtn
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 2
        }
        width: 100
        text: "Ok"
        onClicked: popup.close()
    }

    Component.onCompleted: {
        let fund = 0;
        let diff = 0;

        totalFunding = 0;
        for (let country of Game.savedGame.countries)
        {
            let count = country.funding.length;
            fund = country.funding[count-1];
            if(count > 1)
                diff = fund - country.funding[count-2];
            else
                diff = 0;

            totalFunding += fund;

            fundingProxy.model.append({
                "name": country.name,
                "funding": fund,
                "fundingDiff": diff
            });
        }
    }
}
