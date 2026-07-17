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

#include "CutsceneState.h"
#include "MainMenuState.h"
#include "SlideshowState.h"
#include "VideoState.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Game.h"
#include "../Engine/Logger.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Engine/FileMap.h"
#include "../Mod/Mod.h"
#include "../Savegame/SavedGame.h"
#include "StatisticsState.h"

namespace OpenXcom
{

CutsceneState::CutsceneState(const std::string &cutsceneId)
	: _cutsceneId(cutsceneId)
{
	// empty
}

CutsceneState::~CutsceneState()
{
	// empty
}

void CutsceneState::init()
{
	State::init();

	// pop self off stack and replace with actual player state
	game.popState();

	const RuleVideo *videoRule = game.getMod()->getVideo(_cutsceneId, true);
	if (game.savedGame() && game.savedGame()->getEnding() != END_NONE)
	{
		if (game.savedGame()->getMonthsPassed() > -1)
		{
			game.setState(new StatisticsState);
		}
		else
		{
			game.setSavedGame(0);
			game.setState(new GoToMainMenuState);
		}
	}

	bool fmv = false, slide = false;
	if (!videoRule->getVideos()->empty())
	{
		fmv = FileMap::fileExists(videoRule->getVideos()->front());
	}
	if (!videoRule->getSlides()->empty())
	{
		slide = FileMap::fileExists(videoRule->getSlides()->front().imagePath);
	}

	if (fmv && (!slide || options1.preferredVideo() == Options1::VIDEO_FMV))
	{
		game.pushState(new VideoState(videoRule->getVideos(), videoRule->getAudioTracks(), videoRule->useUfoAudioSequence()));
	}
	else if (slide && (!fmv || options1.preferredVideo() == Options1::VIDEO_SLIDE))
	{
		game.pushState(new SlideshowState(videoRule->getSlideshowHeader(), videoRule->getSlides()));
	}
	else
	{
		Log(LOG_WARNING) << "cutscene definition empty: " << _cutsceneId;
	}
}

bool CutsceneState::initDisplay()
{
	bool letterboxed = options1.keepAspectRatio();
	options1.setkeepAspectRatio(true);
	options1.baseXResolution = Screen::ORIGINAL_WIDTH;
	options1.baseYResolution = Screen::ORIGINAL_HEIGHT;
	game.getScreen()->resetDisplay(false);
	return letterboxed;
}

void CutsceneState::resetDisplay(bool wasLetterboxed)
{
	options1.setkeepAspectRatio(wasLetterboxed);
	Screen::updateScale(options1.geoscapeScale(), options1.baseXGeoscape, options1.baseYGeoscape, true);
	game.getScreen()->resetDisplay(false);
}

}
