import OpenXcom 1.0

ListGames {
    id: popup
    width: 320
    height: 200
    captionKey: "STR_SELECT_SAVE_POSITION"
    editebleNames: true

    function initSavesList() {
        return Game.saves(false);
    }

    onAcceptedSavedGame: (index)=>
    {
        Game.saveGame(saves[index].fileName, saves[index].displayName);
        popup.accept();
    }
}
