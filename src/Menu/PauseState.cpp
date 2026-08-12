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
#include "PauseState.h"
#include "../Engine/Game.h"
#include "../Mod/Mod.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
//#include "ListLoadState.h"
#include "ListSaveState.h"
#include "../Engine/Options.h"
#include "OptionsVideoState.h"
#include "OptionsGeoscapeState.h"
#include "OptionsBattlescapeState.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Battlescape/BattlescapeGame.h"
#include "../version.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Pause window.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 */
PauseState::PauseState(OptionsOrigin origin) : _origin(origin)
{
	_screen = false;

	int x;
	if (_origin == OPT_GEOSCAPE)
	{
		x = 20;
	}
	else
	{
		x = 52;
	}

	// Create objects
	_window = new Window(this, 216, 160, x, 20, POPUP_BOTH);
	_btnLoad = new TextButton(180, 18, x+18, 52);
	_btnSave = new TextButton(180, 18, x+18, 74);
	_btnAbandon = new TextButton(180, 18, x+18, 96);
	_btnOptions = new TextButton(180, 18, x+18, 122);
	_btnCancel = new TextButton(180, 18, x+18, 150);
	_txtTitle = new Text(206, 17, x+5, 32);
	_txtVersion = new Text(216, 9, x, 11);

	// Set palette
	setInterface("pauseMenu", false, game.savedGame() ? game.savedGame()->getSavedBattle() : 0);

	add(_window, "window", "pauseMenu");
	add(_btnLoad, "button", "pauseMenu");
	add(_btnSave, "button", "pauseMenu");
	add(_btnAbandon, "button", "pauseMenu");
	add(_btnOptions, "button", "pauseMenu");
	add(_btnCancel, "button", "pauseMenu");
	add(_txtTitle, "text", "pauseMenu");
	add(_txtVersion, "text", "pauseMenu");

	centerAllSurfaces();

	// Set up objects
	setWindowBackground(_window, "pauseMenu");

	_btnLoad->setText(ltr("STR_LOAD_GAME"));
	_btnLoad->onMouseClick((ActionHandler)&PauseState::btnLoadClick);

	_btnSave->setText(ltr("STR_SAVE_GAME"));
	_btnSave->onMouseClick((ActionHandler)&PauseState::btnSaveClick);

	_btnAbandon->setText(ltr("STR_ABANDON_GAME"));
	_btnAbandon->onMouseClick((ActionHandler)&PauseState::btnAbandonClick);

	_btnOptions->setText(ltr("STR_GAME_OPTIONS"));
	_btnOptions->onMouseClick((ActionHandler)&PauseState::btnOptionsClick);

	_btnCancel->setText(ltr("STR_CANCEL_UC"));
	_btnCancel->onMouseClick((ActionHandler)&PauseState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&PauseState::btnCancelClick, options1.keyCancel());
	if (origin == OPT_GEOSCAPE)
	{
		_btnCancel->onKeyboardPress((ActionHandler)&PauseState::btnCancelClick, options1.keyGeoOptions());
	}
	else if (origin == OPT_BATTLESCAPE)
	{
		_btnCancel->onKeyboardPress((ActionHandler)&PauseState::btnCancelClick, options1.keyBattleOptions());
		if (!game.savedGame()->getSavedBattle()->getBattleGame()->getStates().empty())
		{
			_btnOptions->setVisible(false);
		}
	}

	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setBig();
	_txtTitle->setText(ltr("STR_OPTIONS_UC"));

	std::ostringstream title;
	title << "OpenXcom " << OPENXCOM_VERSION_SHORT;
	_txtVersion->setText(title.str());
	_txtVersion->setAlign(ALIGN_CENTER);

	if (_origin == OPT_BATTLESCAPE)
	{
		applyBattlescapeTheme("pauseMenu");
	}

	if (game.savedGame()->isIronMan())
	{
		_btnLoad->setVisible(false);
		_btnSave->setVisible(false);
		_btnAbandon->setText(ltr("STR_SAVE_AND_ABANDON_GAME"));
	}

	// ENOUGH! No save corruption when trying to save/exit mid-action (e.g. during alien turn)
	if (origin == OPT_BATTLESCAPE)
	{
		bool playerTurn = game.savedGame()->getSavedBattle()->getSide() == FACTION_PLAYER;
		bool debugMode = game.savedGame()->getSavedBattle()->getDebugMode();
		bool busy = !game.savedGame()->getSavedBattle()->getBattleGame()->getStates().empty();

		if ((!playerTurn && !debugMode) || busy)
		{
			_btnSave->setVisible(false); // non-ironman + ironman

			if (game.savedGame()->isIronMan())
			{
				_btnAbandon->setVisible(false); // ironman only
			}
		}
	}
}

/**
 *
 */
PauseState::~PauseState()
{

}

/**
 * Opens the Load Game screen.
 * @param action Pointer to an action.
 */
void PauseState::btnLoadClick(Action *)
{
	createQmlItem("qrc:/OpenXcom/Menu/LoadGame.qml");

	//game.pushState(new ListLoadState(_origin));
}

/**
 * Opens the Save Game screen.
 * @param action Pointer to an action.
 */
void PauseState::btnSaveClick(Action *)
{
	game.pushState(new ListSaveState(_origin));
}

/**
 * Opens the Game Options screen.
 * @param action Pointer to an action.
 */
void PauseState::btnOptionsClick(Action *)
{
	Options::backupDisplay();
	if (_origin == OPT_GEOSCAPE)
	{
		game.pushState(new OptionsGeoscapeState(_origin));
	}
	else if (_origin == OPT_BATTLESCAPE)
	{
		game.pushState(new OptionsBattlescapeState(_origin));
	}
	else
	{
		game.pushState(new OptionsVideoState(_origin));
	}
}

/**
 * Opens the Abandon Game window.
 * @param action Pointer to an action.
 */
void PauseState::btnAbandonClick(Action *)
{
	createQmlItem("qrc:/OpenXcom/Menu/AbandonGame.qml");
}

/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void PauseState::btnCancelClick(Action *)
{
	game.popState();
}

}
