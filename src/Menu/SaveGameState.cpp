/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "SaveGameState.h"

#include "../Engine/Logger.h"
#include "../Engine/Game.h"
#include "../Engine/Exception.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Unicode.h"
#include "../Interface/Text.h"
#include "MainMenuState.h"
#include "../Savegame/SavedGame.h"
#include "../Mod/Mod.h"
#include "../Mod/RuleInterface.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Save Game screen.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 * @param filename Name of the save file without extension.
 * @param palette Parent state palette.
 */
SaveGameState::SaveGameState(OptionsOrigin origin, const std::string &filename, SDL_Color *palette) : _firstRun(0), _origin(origin), _filename(filename), _type(SAVE_DEFAULT)
{
	buildUi(palette);
}

/**
 * Initializes all the elements in the Save Game screen.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 * @param type Type of auto-save being used.
 * @param palette Parent state palette.
 */
SaveGameState::SaveGameState(OptionsOrigin origin, SaveType type, SDL_Color *palette, int currentTurn) : _firstRun(0), _origin(origin), _type(type)
{
	switch (type)
	{
	case SAVE_QUICK:
		_filename = SavedGame::QUICKSAVE;
		break;
	case SAVE_INSTA:
		_filename = "Instasave_" + CrossPlatform::sanitizeFilename(CrossPlatform::now()) + ".sav";
		break;
	case SAVE_AUTO_GEOSCAPE:
		if (options1.oxceGeoAutosaveFrequency() > 0 && options1.oxceGeoAutosaveSlots() >= 2 && options1.oxceGeoAutosaveSlots() <= 10 && currentTurn > 0)
		{
			// multi-slot autosave
			int slotIndex = (currentTurn / options1.oxceGeoAutosaveFrequency()) % options1.oxceGeoAutosaveSlots();
			_filename = "_" + std::to_string(slotIndex) + SavedGame::AUTOSAVE_GEOSCAPE;
		}
		else
		{
			// classic autosave
			_filename = SavedGame::AUTOSAVE_GEOSCAPE;
		}
		break;
	case SAVE_AUTO_BATTLESCAPE:
		if (currentTurn > 0 && options1.autosaveSlots() >= 2 && options1.autosaveSlots() <= 10)
		{
			// multi-slot autosave
			int slotIndex = (currentTurn / options1.autosaveFrequency()) % options1.autosaveSlots();
			_filename = "_" + std::to_string(slotIndex) + SavedGame::AUTOSAVE_BATTLESCAPE;
		}
		else
		{
			// classic autosave
			_filename = SavedGame::AUTOSAVE_BATTLESCAPE;
		}
		break;
	case SAVE_IRONMAN:
	case SAVE_IRONMAN_END:
		_filename = CrossPlatform::sanitizeFilename(game.savedGame()->getName()) + ".sav";
		break;
	default:
		break;
	}

	buildUi(palette);
}

/**
 *
 */
SaveGameState::~SaveGameState()
{

}

/**
 * Builds the interface.
 * @param palette Parent state palette.
 */
void SaveGameState::buildUi(SDL_Color *palette)
{
	_screen = false;

	// Create objects
	_txtStatus = new Text(320, 17, 0, 92);

	// Set palette
	setStatePalette(palette);

	if (_origin == OPT_BATTLESCAPE)
	{
		add(_txtStatus, "textLoad", "battlescape");
		_txtStatus->setHighContrast(true);
	}
	else
	{
		add(_txtStatus, "textLoad", "geoscape");
	}

	centerAllSurfaces();

	// Set up objects
	_txtStatus->setBig();
	_txtStatus->setAlign(ALIGN_CENTER);
	_txtStatus->setText(ltr("STR_SAVING_GAME"));

}

/**
 * Saves the current save.
 */
void SaveGameState::think()
{
	State::think();
	// Make sure it gets drawn properly
	if (_firstRun < 10)
	{
		_firstRun++;
	}
	else
	{
		game.popState();

		switch (_type)
		{
		case SAVE_DEFAULT:
			// manual save, close the save screen
			game.popState();
			if (!game.savedGame()->isIronMan())
			{
				// and pause screen too
				game.popState();
			}
			break;
		case SAVE_INSTA:
			// timestamp is visible already, no need to repeat it
			game.savedGame()->setName(ltr("STR_INSTA_SAVE"));
			break;
		case SAVE_QUICK:
		case SAVE_AUTO_GEOSCAPE:
		case SAVE_AUTO_BATTLESCAPE:
			// automatic save, give it a default name
			game.savedGame()->setName(_filename);
		default:
			break;
		}

		// Save the game
		try
		{
			std::string backup = _filename + ".bak";
			game.savedGame()->save(backup, game.mod());
			std::string fullPath = Options::getMasterUserFolder() + _filename;
			std::string bakPath = Options::getMasterUserFolder() + backup;
			if (!CrossPlatform::moveFile(bakPath, fullPath))
			{
				throw Exception("Save backed up in " + backup);
			}

			if (_type == SAVE_IRONMAN_END)
			{
				Screen::updateScale(options1.geoscapeScale(), options1.baseXGeoscape, options1.baseYGeoscape, true);
				game.getScreen()->resetDisplay(false);

				game.setState(new MainMenuState);
				game.openDialog("qrc:/OpenXcom/Menu/MainMenu.qml");
				game.setSavedGame(0);
			}

			// Clear the SDL event queue (i.e. ignore input from impatient users)
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				// do nothing
			}
		}
		catch (Exception &e)
		{
			error(e.what());
		}
		catch (YAML::Exception &e)
		{
			error(e.what());
		}
	}
}

/**
 * Pops up a window with an error message.
 * @param msg Error message.
 */
void SaveGameState::error(const std::string &msg)
{
	Log(LOG_ERROR) << msg;
	std::ostringstream error;
	error << ltr("STR_SAVE_UNSUCCESSFUL") << Unicode::TOK_NL_SMALL << msg;
	if (_origin != OPT_BATTLESCAPE)
		game.errorMessage(QString::fromStdString(error.str()));
	else
		game.errorMessage(QString::fromStdString(error.str()));
}

}
