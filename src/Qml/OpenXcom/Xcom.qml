pragma Singleton

import QtQuick

QtObject {

    function createWindow(url, owner, params)
    {
        let cmp = Qt.createComponent(url)
        let obj = null
        if (cmp.status === Component.Ready)
            obj = cmp.createObject(owner, params);
        else
            console.log(cmp.errorString())

        return obj;
    }
}
