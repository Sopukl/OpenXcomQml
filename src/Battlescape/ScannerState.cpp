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
#include "ScannerState.h"
#include "ScannerView.h"
#include "BattlescapeGame.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Game.h"
#include "../Engine/Action.h"
#include "../Engine/Timer.h"
#include "../Engine/Screen.h"
#include "../Engine/Options.h"
#include "../Savegame/BattleUnit.h"
#include "../Mod/Mod.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/SavedBattleGame.h"

namespace OpenXcom
{

/**
 * Initializes the Scanner State.
 * @param game Pointer to the core game.
 * @param action Pointer to an action.
 */
ScannerState::ScannerState (BattleAction *action) : _action(action)
{
	if (options1.maximizeInfoScreens())
	{
		options1.baseXResolution = Screen::ORIGINAL_WIDTH;
		options1.baseYResolution = Screen::ORIGINAL_HEIGHT;
		game.getScreen()->resetDisplay(false);
	}
	_bg = new InteractiveSurface(320, 200);
	_scan = new Surface(320, 200);
	_scannerView = new ScannerView(152, 152, 56, 24, _action->actor);

	if (game.getScreen()->getDY() > 50)
	{
		_screen = false;
	}

	// Set palette
	game.savedGame()->getSavedBattle()->setPaletteByDepth(this);

	add(_scan);
	add(_scannerView);
	add(_bg);

	centerAllSurfaces();

	game.mod()->getSurface("DETBORD.PCK")->blitNShade(_bg, 0, 0);
	game.mod()->getSurface("DETBORD2.PCK")->blitNShade(_scan, 0, 0);
	_bg->onMouseClick((ActionHandler)&ScannerState::exitClick);
	_bg->onKeyboardPress((ActionHandler)&ScannerState::exitClick, options1.keyCancel());

	_timerAnimate = new Timer(125);
	_timerAnimate->onTimer((StateHandler)&ScannerState::animate);
	_timerAnimate->start();

	update();
}

ScannerState::~ScannerState()
{
	delete _timerAnimate;
}

/**
 * Closes the window on right-click.
 * @param action Pointer to an action.
 */
void ScannerState::handle(Action *action)
{
	State::handle(action);
	if (action->getDetails()->type == SDL_MOUSEBUTTONDOWN && game.isRightClick(action))
	{
		exitClick(action);
	}
}

/**
 * Updates scanner state.
 */
void ScannerState::update()
{
	//_scannerView->draw();
}

/**
 * Animation handler. Updates the minimap view animation.
 */
void ScannerState::animate()
{
	_scannerView->animate();
}

/**
 * Handles timers.
 */
void ScannerState::think()
{
	State::think();
	_timerAnimate->think(this, 0);
}

/**
 * Exits the screen.
 * @param action Pointer to an action.
 */
void ScannerState::exitClick(Action *)
{
	if (options1.maximizeInfoScreens())
	{
		Screen::updateScale(options1.battlescapeScale(), options1.baseXBattlescape, options1.baseYBattlescape, true);
		game.getScreen()->resetDisplay(false);
	}
	game.popState();
}

}
