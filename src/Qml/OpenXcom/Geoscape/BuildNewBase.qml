import QtQuick 2.15
import OpenXcom 1.0
import "../Controls" as XC

MouseArea {
    id: ctrl
    anchors.fill: parent
    required property GeoscapeState geoscape
    required property Base base
    required property bool isFirst

    acceptedButtons: Qt.AllButtons
    hoverEnabled: true
    onPositionChanged: geoscape.setBuildNewBasePos(mouseX, mouseY)
    onClicked: (mouse) =>
    {
        if(mouse.button === Qt.RightButton)
            geoscape.globeCenterAt(mouseX, mouseY)
        else
        if(mouse.button === Qt.LeftButton)
        {
            if(geoscape.buildNewBaseAt(mouseX, mouseY, base, isFirst))
                setupBase();
            else
                Xcom.createWindow("qrc:/OpenXcom/Controls/ErrorMessage.qml", ctrl,
                              {errorText: "YOU CANNON BIULD BASE THERE!!!"}).open()
        }
    }

    function setupBase() {
        // if(isFirst)
            setupBaseName()
        // else
        //     Xcom.createWindow("qrc:/OpenXcom/Controls/ErrorMessage.qml", ctrl,
        //                   {errorText: "ARE SOU SHURE???"}).open()
    }

    function setupBaseName() {
        let popup = Xcom.createWindow("Geoscape/BaseName.qml", ctrl);
        popup.done.connect(()=>{
            base.set_Name(popup.baseName);
            popup.destroy();
            ctrl.destroy();
        })
        popup.open();
    }

    function setupBaseContent() {

    }

    Component.onCompleted: forceActiveFocus()
}
