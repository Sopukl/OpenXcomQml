import OpenXcom 1.0

ListGames {
    id: popup
    width: 320
    height: 200

    function initSavesList() {
        return Game.saves();
    }

    onAcceptedSavedGame: (index)=>
    {
        Game.loadGame(saves[index].fileName)
        popup.accept();
    }
}
