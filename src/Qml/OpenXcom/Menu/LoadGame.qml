import OpenXcom 1.0

ListGames {
    id: popup
    width: 320
    height: 200

    onAcceptedSavedGame: (index)=>
    {
        Game.loadGame(saves[index].fileName)
    }
}
