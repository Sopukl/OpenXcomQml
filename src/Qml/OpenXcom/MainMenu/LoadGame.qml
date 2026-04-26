import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels
import OpenXcom 1.0
import OpenXcom.MainMenu.Controls 1.0 as XC

XC.Popup {
    id: popup
    width: 320
    height: 200

    property var descriptions: []
    readonly property var headerTitles: ["Имя", "Дата", "Время", "Описание"]
    readonly property var sortKeys: ["name", "date", "time", "description"]

    property int sortColumn: -1
    property bool sortAscending: true

    function parseDateDMY(s) {
        let p = String(s).split(".")
        if (p.length !== 3)
            return 0
        return new Date(Number(p[2]), Number(p[1]) - 1, Number(p[0])).getTime()
    }

    function parseTimeHMS(s) {
        let p = String(s).split(":")
        if (p.length !== 3)
            return 0
        return ((Number(p[0]) * 60 + Number(p[1])) * 60) + Number(p[2])
    }

    function applyColumnSort(col) {
        if (sortColumn === col)
            sortAscending = !sortAscending
        else {
            sortColumn = col
            sortAscending = true
        }
        let key = sortKeys[col]
        let arr = []
        for (let i = 0; i < gameTable.rowCount; i++)
            arr.push(gameTable.getRow(i))
        arr.sort((a, b) => {
            let va = a[key]
            let vb = b[key]
            let cmp = 0
            if (key === "date")
                cmp = parseDateDMY(va) - parseDateDMY(vb)
            else if (key === "time")
                cmp = parseTimeHMS(va) - parseTimeHMS(vb)
            else
                cmp = String(va).localeCompare(String(vb), undefined, { numeric: true })
            return sortAscending ? cmp : -cmp
        })
        gameTable.clear()
        descriptions.length = 0
        for (let i = 0; i < arr.length; i++) {
            descriptions.push(arr[i].description)
            gameTable.appendRow(arr[i])
        }
    }

    TableModel {
        id: gameTable
        TableModelColumn { display: "checked" }
        TableModelColumn { display: "amount" }
        TableModelColumn { display: "fruitType" }
        TableModelColumn { display: "fruitName" }
        TableModelColumn { display: "fruitPrice" }

        // Each row is one type of fruit that can be ordered
        Component.onCompleted: {
            appendRow(            {
              // Each property is one cell/column.
              checked: false,
              amount: 1,
              fruitType: "Apple",
              fruitName: "Granny Smith",
              fruitPrice: 1.50
          })
            appendRow(
                {
                    checked: true,
                    amount: 4,
                    fruitType: "Orange",
                    fruitName: "Navel",
                    fruitPrice: 2.50})
            appendRow(
                {
                    checked: false,
                    amount: 1,
                    fruitType: "Banana",
                    fruitName: "Cavendish",
                    fruitPrice: 3.50})
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 4

        Text {
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 10
            color: "white"
            text: "Select save game for loading"
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            HorizontalHeaderView {
                id: horizontalHeader
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 24
                syncView: tableView
                clip: true
                z: 1

                delegate: Rectangle {
                    implicitHeight: 24
                    color: "#2a5040"
                    border.width: 1
                    border.color: "#3a7060"

                    required property int column

                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 9
                        color: "white"
                        text: popup.headerTitles[column]
                              + (popup.sortColumn === column ? (popup.sortAscending ? " ▲" : " ▼") : "")
                    }

                    TapHandler {
                        onTapped: popup.applyColumnSort(column)
                    }
                }
            }

            TableView {
                id: tableView
                anchors.top: horizontalHeader.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                clip: true
                //columnSpacing: 1
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds

                model: gameTable

                columnWidthProvider: function (col) {
                    return (tableView.width - tableView.columnSpacing * 3) / 4
                }

                delegate:  Text {
                             text: model.display

                             Rectangle {
                                 anchors.fill: parent
                                 color: "#efefef"
                                 z: -1
                             }
                         }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Text {
                font.pixelSize: 9
                color: "white"
                text: "подробно"
            }

            Text {
                id: descriptionText
                Layout.fillWidth: true
                font.pixelSize: 9
                color: "#a0dcc8"
                wrapMode: Text.WordWrap
                text: ""
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8

            XC.Button {
                text: "Загрузить"
                onClicked: popup.close()
            }

            XC.Button {
                text: "Отмена"
                onClicked: popup.close()
            }
        }
    }
}
