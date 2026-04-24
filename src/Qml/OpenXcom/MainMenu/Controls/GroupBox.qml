import QtQuick
import QtQuick.Controls

GroupBox {
    id: control
    padding: 0
    spacing: 0
    background: null

    label: Label {
        width: control.availableWidth
        text: control.title
        font.pixelSize: 8
        color: "#A8BC50"
        elide: Text.ElideLeft
        horizontalAlignment: Text.AlignLeft
        x: 2
    }
}
