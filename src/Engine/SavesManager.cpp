#include "SavesManager.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Savegame/SavedGame.h"
#include "Game.h"

namespace OpenXcom
{
	// SavesManager::SavesManager(QObject* parent)
	// 	: QObject{parent}
	// {
	// }

	// QVector<SaveDesc> SavesManager::saves() const
	// {
	// 	auto _saves = SavedGame::getList(game.getLanguage(), true);
	// 	QVector<SaveDesc> result;

	// 	for(const auto& s: _saves)
	// 	{
	// 		SaveDesc sd;
	// 		sd.fileName    = QString::fromStdString(s.fileName);
	// 		sd.displayName = QString::fromStdString(s.displayName);
	// 		sd.isoDate     = QString::fromStdString(s.isoDate);
	// 		sd.isoTime     = QString::fromStdString(s.isoTime);
	// 		sd.details     = QString::fromStdString(s.details);
	// 		result.push_back(sd);
	// 	}
	// 	_saves = SavedGame::getList(game.getLanguage(), false);

	// 	return result;
	// }
}
