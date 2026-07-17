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
#include "OptionsBaseState.h"
#include <SDL.h>
#include "../Engine/Game.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Mod/Mod.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/SavedBattleGame.h"
#include "../Interface/Window.h"
#include "../Interface/TextButton.h"
#include "../Interface/Text.h"
#include "../Engine/Action.h"
#include "MainMenuState.h"
#include "../Geoscape/GeoscapeState.h"
#include "../Battlescape/BattlescapeState.h"
#include "OptionsVideoState.h"
#include "OptionsAudioState.h"
#include "OptionsFoldersState.h"
#include "OptionsNoAudioState.h"
#include "OptionsControlsState.h"
#include "OptionsGeoscapeState.h"
#include "OptionsBattlescapeState.h"
#include "OptionsAdvancedState.h"
#include "OptionsDefaultsState.h"
#include "OptionsConfirmState.h"
#include "StartState.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Options window.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 */
OptionsBaseState::OptionsBaseState(OptionsOrigin origin) : _origin(origin), _group(0)
{
	// Create objects
	_window = new Window(this, 320, 200, 0, 0);

	_btnVideo = new TextButton(80, 16, 8, 8);
	_btnAudio = new TextButton(80, 16, 8, 28);
	_btnControls = new TextButton(80, 16, 8, 48);
	_btnGeoscape = new TextButton(80, 16, 8, 68);
	_btnBattlescape = new TextButton(80, 16, 8, 88);
	_btnAdvanced = new TextButton(80, 16, 8, 108);
	_btnFolders = new TextButton(80, 16, 8, 128);

	_btnOk = new TextButton(100, 16, 8, 176);
	_btnCancel = new TextButton(100, 16, 110, 176);
	_btnDefault = new TextButton(100, 16, 212, 176);

	_txtTooltip = new Text(305, 25, 8, 148);

	// Set palette
	setInterface("optionsMenu", false, game.savedGame() ? game.savedGame()->getSavedBattle() : 0);

	add(_window, "window", "optionsMenu");

	add(_btnVideo, "button", "optionsMenu");
	add(_btnAudio, "button", "optionsMenu");
	add(_btnControls, "button", "optionsMenu");
	add(_btnGeoscape, "button", "optionsMenu");
	add(_btnBattlescape, "button", "optionsMenu");
	add(_btnAdvanced, "button", "optionsMenu");
	add(_btnFolders, "button", "optionsMenu");

	add(_btnOk, "button", "optionsMenu");
	add(_btnCancel, "button", "optionsMenu");
	add(_btnDefault, "button", "optionsMenu");

	add(_txtTooltip, "tooltip", "optionsMenu");

	// Set up objects
	setWindowBackground(_window, "optionsMenu");

	_btnVideo->setText(ltr("STR_VIDEO"));
	_btnVideo->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnAudio->setText(ltr("STR_AUDIO"));
	_btnAudio->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnControls->setText(ltr("STR_CONTROLS"));
	_btnControls->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnGeoscape->setText(ltr("STR_GEOSCAPE_UC"));
	_btnGeoscape->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnBattlescape->setText(ltr("STR_BATTLESCAPE_UC"));
	_btnBattlescape->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnAdvanced->setText(ltr("STR_ADVANCED"));
	_btnAdvanced->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnFolders->setText(ltr("STR_FOLDERS"));
	_btnFolders->onMousePress((ActionHandler)&OptionsBaseState::btnGroupPress, SDL_BUTTON_LEFT);

	_btnOk->setText(ltr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&OptionsBaseState::btnOkClick);
	_btnOk->onKeyboardPress((ActionHandler)&OptionsBaseState::btnOkClick, options1.keyOk());

	_btnCancel->setText(ltr("STR_CANCEL"));
	_btnCancel->onMouseClick((ActionHandler)&OptionsBaseState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&OptionsBaseState::btnCancelClick, options1.keyCancel());

	_btnDefault->setText(ltr("STR_RESTORE_DEFAULTS"));
	_btnDefault->onMouseClick((ActionHandler)&OptionsBaseState::btnDefaultClick);

	_txtTooltip->setWordWrap(true);
}

/**
 *
 */
OptionsBaseState::~OptionsBaseState()
{

}

void OptionsBaseState::restart(OptionsOrigin origin)
{
	// Reset touch flags
	game.resetTouchButtonFlags();

	if (origin == OPT_MENU)
	{
		game.setState(new MainMenuState);
	}
	else if (origin == OPT_GEOSCAPE)
	{
		game.setState(new GeoscapeState);
	}
	else if (origin == OPT_BATTLESCAPE)
	{
		BattlescapeState *origBattleState = 0;
		if (game.savedGame() != 0 && game.savedGame()->getSavedBattle() != 0)
		{
			origBattleState = game.savedGame()->getSavedBattle()->getBattleState();
		}
		if (origBattleState != 0)
		{
			// We need to reset palettes here already, can't wait for the destructor
			origBattleState->resetPalettes();
		}

		game.setState(new GeoscapeState);
		BattlescapeState *bs = new BattlescapeState;
		game.pushState(bs);
		game.savedGame()->getSavedBattle()->setBattleState(bs);
		// Try to reactivate the touch buttons
		bs->toggleTouchButtons(false, true);
	}
}

/**
 * Initializes UI colors according to origin.
 */
void OptionsBaseState::init()
{
	State::init();
	if (_origin == OPT_BATTLESCAPE)
	{
		applyBattlescapeTheme("optionsMenu");
	}
}

/**
 * Handles the pressed-button state for the category buttons.
 * @param button Button to press.
 */
void OptionsBaseState::setCategory(TextButton *button)
{
	_group = button;
	_btnVideo->setGroup(&_group);
	_btnAudio->setGroup(&_group);
	_btnControls->setGroup(&_group);
	_btnGeoscape->setGroup(&_group);
	_btnBattlescape->setGroup(&_group);
	_btnAdvanced->setGroup(&_group);
	_btnFolders->setGroup(&_group);
}

/**
 * Saves the new options and returns to the proper origin screen.
 * @param action Pointer to an action.
 */
void OptionsBaseState::btnOkClick(Action *)
{
	Options::switchDisplay();
	int dX = options1.baseXResolution;
	int dY = options1.baseYResolution;
	Screen::updateScale(options1.battlescapeScale(), options1.baseXBattlescape, options1.baseYBattlescape, _origin == OPT_BATTLESCAPE);
	Screen::updateScale(options1.geoscapeScale(), options1.baseXGeoscape, options1.baseYGeoscape, _origin != OPT_BATTLESCAPE);
	dX = options1.baseXResolution - dX;
	dY = options1.baseYResolution - dY;
	recenter(dX, dY);
	Options::save();
	game.loadLanguages();
	game.getScreen()->resetDisplay();
	SDL_WM_GrabInput(SDL_GrabMode(options1.captureMouse()));
	game.setVolume(options1.soundVolume(), options1.musicVolume(), options1.uiVolume());
	if (options1.reload && _origin == OPT_MENU)
	{
		game.setState(new StartState);
	}
	else
	{
		// Confirm any video options changes
		if (options1.displayWidth() != options1.newDisplayWidth ||
			options1.displayHeight() != options1.newDisplayHeight ||
			options1.useOpenGL() != options1.newOpenGL ||
			options1.useScaleFilter() != options1.newScaleFilter ||
			options1.useHQXFilter() != options1.newHQXFilter ||
			options1.useOpenGLShader() != options1.newOpenGLShader)
		{
			game.pushState(new OptionsConfirmState(_origin));
		}
		else
		{
			restart(_origin);
		}
	}
}

/**
 * Loads previous options and returns to the previous screen.
 * @param action Pointer to an action.
 */
void OptionsBaseState::btnCancelClick(Action *)
{
	options1.reload = false;
	Options::load();
	SDL_WM_GrabInput(SDL_GrabMode(options1.captureMouse()));
	Screen::updateScale(options1.battlescapeScale(), options1.baseXBattlescape, options1.baseYBattlescape, _origin == OPT_BATTLESCAPE);
	Screen::updateScale(options1.geoscapeScale(), options1.baseXGeoscape, options1.baseYGeoscape, _origin != OPT_BATTLESCAPE);
	game.setVolume(options1.soundVolume(), options1.musicVolume(), options1.uiVolume());
	game.popState();
}

/**
 * Restores the Options to default settings.
 * @param action Pointer to an action.
 */
void OptionsBaseState::btnDefaultClick(Action *)
{
	game.pushState(new OptionsDefaultsState(_origin, this));
}

void OptionsBaseState::btnGroupPress(Action *action)
{
	Surface *sender = action->getSender();
	//if (sender != _group)
	{
		game.popState();
		if (sender == _btnVideo)
		{
			game.pushState(new OptionsVideoState(_origin));
		}
		else if (sender == _btnAudio)
		{
			// if (!options1.mute)
			// {
				game.pushState(new OptionsAudioState(_origin));
			// }
			// else
			// {
				// game.pushState(new OptionsNoAudioState(_origin));
			// }
		}
		else if (sender == _btnControls)
		{
			game.pushState(new OptionsControlsState(_origin));
		}
		else if (sender == _btnGeoscape)
		{
			game.pushState(new OptionsGeoscapeState(_origin));
		}
		else if (sender == _btnBattlescape)
		{
			game.pushState(new OptionsBattlescapeState(_origin));
		}
		else if (sender == _btnAdvanced)
		{
			game.pushState(new OptionsAdvancedState(_origin));
		}
		else if (sender == _btnFolders)
		{
			game.pushState(new OptionsFoldersState(_origin));
		}
	}
}

/**
 * Shows a tooltip for the appropriate button.
 * @param action Pointer to an action.
 */
void OptionsBaseState::txtTooltipIn(Action *action)
{
	_currentTooltip = action->getSender()->getTooltip();
	_txtTooltip->setText(ltr(_currentTooltip));
}

/**
 * Clears the tooltip text.
 * @param action Pointer to an action.
 */
void OptionsBaseState::txtTooltipOut(Action *action)
{
	if (_currentTooltip == action->getSender()->getTooltip())
	{
		_txtTooltip->setText("");
	}
}

/**
 * Updates the scale.
 * @param dX delta of X;
 * @param dY delta of Y;
 */
void OptionsBaseState::resize(int &dX, int &dY)
{
	options1.newDisplayWidth = options1.displayWidth();
	options1.newDisplayHeight = options1.displayHeight();
	State::resize(dX, dY);
}

}
