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
#include "OptionsVideoState.h"
#include "../Engine/Game.h"
#include "../Interface/TextButton.h"
#include "../Engine/Action.h"
#include "../Interface/Text.h"
#include "../Interface/TextEdit.h"
#include "../Interface/ToggleTextButton.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Interface/ArrowButton.h"
#include "../Engine/FileMap.h"
#include "../Engine/Logger.h"
#include "../Interface/ComboBox.h"
#include "../Engine/Game.h"
#include "SetWindowedRootState.h"

namespace OpenXcom
{

const std::string OptionsVideoState::GL_EXT = "OpenGL.shader";
const std::string OptionsVideoState::GL_FOLDER = "Shaders/";
const std::string OptionsVideoState::GL_STRING = "*";

/**
 * Initializes all the elements in the Video Options screen.
 * @param game Pointer to the core game.
 * @param origin Game section that originated this state.
 */
OptionsVideoState::OptionsVideoState(OptionsOrigin origin) : OptionsBaseState(origin)
{
	setCategory(_btnVideo);

	// Create objects
	_displaySurface = new InteractiveSurface(110, 32, 94, 18);
	_txtDisplayResolution = new Text(114, 9, 94, 8);
	_txtDisplayWidth = new TextEdit(this, 40, 17, 94, 26);
	_txtDisplayX = new Text(16, 17, 132, 26);
	_txtDisplayHeight = new TextEdit(this, 40, 17, 144, 26);
	_btnDisplayResolutionUp = new ArrowButton(ARROW_BIG_UP, 14, 14, 186, 18);
	_btnDisplayResolutionDown = new ArrowButton(ARROW_BIG_DOWN, 14, 14, 186, 36);

	_txtLanguage = new Text(114, 9, 94, 52);
	_cbxLanguage = new ComboBox(this, 104, 16, 94, 62);

	_txtFilter = new Text(114, 9, 206, 52);
	_cbxFilter = new ComboBox(this, 104, 16, 206, 62);

	_txtMode = new Text(114, 9, 206, 22);
	_cbxDisplayMode = new ComboBox(this, 104, 16, 206, 32);

	_txtGeoScale = new Text(114, 9, 94, 82);
	_cbxGeoScale = new ComboBox(this, 104, 16, 94, 92);

	_txtBattleScale = new Text(114, 9, 94, 112);
	_cbxBattleScale = new ComboBox(this, 104, 16, 94, 122);

	_txtOptions = new Text(114, 9, 206, 82);
	_btnLetterbox = new ToggleTextButton(104, 16, 206, 92);
	_btnLockMouse = new ToggleTextButton(104, 16, 206, 110);
	_btnRootWindowedMode = new ToggleTextButton(104, 16, 206, 128);

	// Get available fullscreen modes
	_res = SDL_ListModes(NULL, SDL_FULLSCREEN);
	if (_res != (SDL_Rect**)-1 && _res != (SDL_Rect**)0)
	{
		int i;
		_resCurrent = -1;
		for (i = 0; _res[i]; ++i)
		{
			if (_resCurrent == -1 &&
				((_res[i]->w == options1.displayWidth() && _res[i]->h <= options1.displayHeight()) || _res[i]->w < options1.displayWidth()))
			{
				_resCurrent = i;
			}
		}
		_resAmount = i;
	}
	else
	{
		_resCurrent = -1;
		_resAmount = 0;
		_btnDisplayResolutionDown->setVisible(false);
		_btnDisplayResolutionUp->setVisible(false);
		Log(LOG_WARNING) << "Couldn't get display resolutions";
	}

	add(_displaySurface);
	add(_txtDisplayResolution, "text", "videoMenu");
	add(_txtDisplayWidth, "resolution", "videoMenu");
	add(_txtDisplayX, "resolution", "videoMenu");
	add(_txtDisplayHeight, "resolution", "videoMenu");
	add(_btnDisplayResolutionUp, "button", "videoMenu");
	add(_btnDisplayResolutionDown, "button", "videoMenu");

	add(_txtLanguage, "text", "videoMenu");
	add(_txtFilter, "text", "videoMenu");

	add(_txtMode, "text", "videoMenu");

	add(_txtOptions, "text", "videoMenu");
	add(_btnLetterbox, "button", "videoMenu");
	add(_btnLockMouse, "button", "videoMenu");
	add(_btnRootWindowedMode, "button", "videoMenu");

	add(_cbxFilter, "button", "videoMenu");
	add(_cbxDisplayMode, "button", "videoMenu");

	add(_txtBattleScale, "text", "videoMenu");
	add(_cbxBattleScale, "button", "videoMenu");

	add(_txtGeoScale, "text", "videoMenu");
	add(_cbxGeoScale, "button", "videoMenu");

	add(_cbxLanguage, "button", "videoMenu");
	centerAllSurfaces();

	// Set up objects
	_txtDisplayResolution->setText(ltr("STR_DISPLAY_RESOLUTION"));

	_displaySurface->setTooltip("STR_DISPLAY_RESOLUTION_DESC");
	_displaySurface->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_displaySurface->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtDisplayWidth->setAlign(ALIGN_CENTER);
	_txtDisplayWidth->setBig();
	_txtDisplayWidth->setConstraint(TEC_NUMERIC_POSITIVE);
	_txtDisplayWidth->onChange((ActionHandler)&OptionsVideoState::txtDisplayWidthChange);

	_txtDisplayX->setAlign(ALIGN_CENTER);
	_txtDisplayX->setBig();
	_txtDisplayX->setText("x");

	_txtDisplayHeight->setAlign(ALIGN_CENTER);
	_txtDisplayHeight->setBig();
	_txtDisplayHeight->setConstraint(TEC_NUMERIC_POSITIVE);
	_txtDisplayHeight->onChange((ActionHandler)&OptionsVideoState::txtDisplayHeightChange);

	std::ostringstream ssW, ssH;
	ssW << options1.displayWidth();
	ssH << options1.displayHeight();
	_txtDisplayWidth->setText(ssW.str());
	_txtDisplayHeight->setText(ssH.str());

	_btnDisplayResolutionUp->onMouseClick((ActionHandler)&OptionsVideoState::btnDisplayResolutionUpClick);
	_btnDisplayResolutionDown->onMouseClick((ActionHandler)&OptionsVideoState::btnDisplayResolutionDownClick);

	_txtMode->setText(ltr("STR_DISPLAY_MODE"));

	_txtOptions->setText(ltr("STR_DISPLAY_OPTIONS"));

	_btnLetterbox->setText(ltr("STR_LETTERBOXED"));
	_btnLetterbox->setPressed(options1.keepAspectRatio());
	_btnLetterbox->onMouseClick((ActionHandler)&OptionsVideoState::btnLetterboxClick);
	_btnLetterbox->setTooltip("STR_LETTERBOXED_DESC");
	_btnLetterbox->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_btnLetterbox->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_btnLockMouse->setText(ltr("STR_LOCK_MOUSE"));
	_btnLockMouse->setPressed(options1.captureMouse() == SDL_GRAB_ON);
	_btnLockMouse->onMouseClick((ActionHandler)&OptionsVideoState::btnLockMouseClick);
	_btnLockMouse->setTooltip("STR_LOCK_MOUSE_DESC");
	_btnLockMouse->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_btnLockMouse->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_btnRootWindowedMode->setText(ltr("STR_FIXED_WINDOW_POSITION"));
	_btnRootWindowedMode->setPressed(options1.rootWindowedMode());
	_btnRootWindowedMode->onMouseClick((ActionHandler)&OptionsVideoState::btnRootWindowedModeClick);
	_btnRootWindowedMode->setTooltip("STR_FIXED_WINDOW_POSITION_DESC");
	_btnRootWindowedMode->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_btnRootWindowedMode->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtLanguage->setText(ltr("STR_DISPLAY_LANGUAGE"));

	std::vector<std::string> names;
	Language::getList(_langs, names);
	_cbxLanguage->setOptions(names);
	for (size_t i = 0; i < names.size(); ++i)
	{
		if (_langs[i] == options1.language().toStdString())
		{
			_cbxLanguage->setSelected(i);
			break;
		}
	}
	_cbxLanguage->onChange((ActionHandler)&OptionsVideoState::cbxLanguageChange);
	_cbxLanguage->setTooltip("STR_DISPLAY_LANGUAGE_DESC");
	_cbxLanguage->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxLanguage->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	std::vector<std::string> filterNames;
	filterNames.push_back(ltr("STR_DISABLED"));
	filterNames.push_back("Scale");
	filterNames.push_back("HQx");
	filterNames.push_back("xBRZ");
	_filters.push_back("");
	_filters.push_back("");
	_filters.push_back("");
	_filters.push_back("");

#ifndef __NO_OPENGL
	std::vector<std::string> filters;
	for (const auto& f : FileMap::filterFiles(FileMap::getVFolderContents(GL_FOLDER), GL_EXT)) { filters.push_back(f); }
	std::sort(filters.begin(), filters.end(), Unicode::naturalCompare);
	for (const auto& file : filters)
	{
		std::string path = GL_FOLDER + file;
		std::string name = file.substr(0, file.length() - GL_EXT.length() - 1) + GL_STRING;
		filterNames.push_back(ucWords(name));
		_filters.push_back(path);
	}
#endif

	size_t selFilter = 0;
	if (Screen::useOpenGL())
	{
#ifndef __NO_OPENGL
		std::string path = options1.useOpenGLShader().toStdString();
		for (size_t i = 0; i < _filters.size(); ++i)
		{
			if (_filters[i] == path)
			{
				selFilter = i;
				break;
			}
		}
#endif
	}
	else if (options1.useScaleFilter())
	{
		selFilter = 1;
	}
	else if (options1.useHQXFilter())
	{
		selFilter = 2;
	}
	else if (options1.useXBRZFilter())
	{
		selFilter = 3;
	}

	_txtFilter->setText(ltr("STR_DISPLAY_FILTER"));

	_cbxFilter->setOptions(filterNames);
	_cbxFilter->setSelected(selFilter);
	_cbxFilter->onChange((ActionHandler)&OptionsVideoState::cbxFilterChange);
	_cbxFilter->setTooltip("STR_DISPLAY_FILTER_DESC");
	_cbxFilter->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxFilter->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);


	std::vector<std::string> displayModes;
	displayModes.push_back(ltr("STR_WINDOWED"));
	displayModes.push_back(ltr("STR_FULLSCREEN"));
	displayModes.push_back(ltr("STR_BORDERLESS"));
	displayModes.push_back(ltr("STR_RESIZABLE"));

	int displayMode = 0;
	if (options1.fullscreen())
	{
		displayMode = 1;
	}
	else if (options1.borderless())
	{
		displayMode = 2;
	}
	else if (options1.allowResize())
	{
		displayMode = 3;
	}

	_cbxDisplayMode->setOptions(displayModes);
	_cbxDisplayMode->setSelected(displayMode);
	_cbxDisplayMode->onChange((ActionHandler)&OptionsVideoState::updateDisplayMode);
	_cbxDisplayMode->setTooltip("STR_DISPLAY_MODE_DESC");
	_cbxDisplayMode->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxDisplayMode->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtGeoScale->setText(ltr("STR_GEOSCAPE_SCALE"));

	std::vector<std::string> scales;
	scales.push_back("1x"); // was 5 -> is 0
	scales.push_back("2x"); // was 4 -> is 1
	scales.push_back("3x"); // was 3 -> is 2
	scales.push_back("4x"); // was 6 -> is 3
	scales.push_back("5x"); // was 7 -> is 4
	scales.push_back("6x"); // was 8 -> is 5
	scales.push_back("320x200"); // was 0 -> is 6
	scales.push_back("480x300"); // was 1 -> is 7
	scales.push_back("640x400"); // was 2 -> is 8
	scales.push_back("8x");  // new 9
	scales.push_back("10x"); // new 10

	_scales.push_back(6); // 0
	_scales.push_back(7); // 1
	_scales.push_back(8); // 2
	_scales.push_back(2); // 3
	_scales.push_back(1); // 4
	_scales.push_back(0); // 5
	_scales.push_back(3); // 6
	_scales.push_back(4); // 7
	_scales.push_back(5); // 8
	_scales.push_back(9);
	_scales.push_back(10);

	_reverseScales.push_back(5); // 0
	_reverseScales.push_back(4); // 1
	_reverseScales.push_back(3); // 2
	_reverseScales.push_back(6); // 3
	_reverseScales.push_back(7); // 4
	_reverseScales.push_back(8); // 5
	_reverseScales.push_back(0); // 6
	_reverseScales.push_back(1); // 7
	_reverseScales.push_back(2); // 8
	_reverseScales.push_back(9);
	_reverseScales.push_back(10);

	if (options1.geoscapeScale() < 0 || options1.geoscapeScale() > 10) options1.setgeoscapeScale(0);
	if (options1.battlescapeScale() < 0 || options1.battlescapeScale() > 10) options1.setbattlescapeScale(0);

	_cbxGeoScale->setOptions(scales);
	_cbxGeoScale->setSelected(_scales[options1.geoscapeScale()]);
	_cbxGeoScale->onChange((ActionHandler)&OptionsVideoState::updateGeoscapeScale);
	_cbxGeoScale->setTooltip("STR_GEOSCAPESCALE_SCALE_DESC");
	_cbxGeoScale->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxGeoScale->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

	_txtBattleScale->setText(ltr("STR_BATTLESCAPE_SCALE"));

	_cbxBattleScale->setOptions(scales);
	_cbxBattleScale->setSelected(_scales[options1.battlescapeScale()]);
	_cbxBattleScale->onChange((ActionHandler)&OptionsVideoState::updateBattlescapeScale);
	_cbxBattleScale->setTooltip("STR_BATTLESCAPE_SCALE_DESC");
	_cbxBattleScale->onMouseIn((ActionHandler)&OptionsVideoState::txtTooltipIn);
	_cbxBattleScale->onMouseOut((ActionHandler)&OptionsVideoState::txtTooltipOut);

}

/**
 *
 */
OptionsVideoState::~OptionsVideoState()
{

}

/**
 * Uppercases all the words in a string.
 * @param str Source string.
 * @return Destination string.
 */
std::string OptionsVideoState::ucWords(std::string str)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (i == 0)
			str[0] = toupper(str[0]);
		else if (str[i] == ' ' || str[i] == '-' || str[i] == '_')
		{
			str[i] = ' ';
			if (str.length() > i + 1)
				str[i + 1] = toupper(str[i + 1]);
		}
	}
	return str;
}

/**
 * Selects a bigger display resolution.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnDisplayResolutionUpClick(Action *)
{
	if (_resAmount == 0)
		return;
	if (_resCurrent <= 0)
	{
		_resCurrent = _resAmount-1;
	}
	else
	{
		_resCurrent--;
	}
	updateDisplayResolution();
}

/**
 * Selects a smaller display resolution.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnDisplayResolutionDownClick(Action *)
{
	if (_resAmount == 0)
		return;
	if (_resCurrent >= _resAmount-1)
	{
		_resCurrent = 0;
	}
	else
	{
		_resCurrent++;
	}
	updateDisplayResolution();
}

/**
 * Updates the display resolution based on the selection.
 */
void OptionsVideoState::updateDisplayResolution()
{
	std::ostringstream ssW, ssH;
	ssW << (int)_res[_resCurrent]->w;
	ssH << (int)_res[_resCurrent]->h;
	_txtDisplayWidth->setText(ssW.str());
	_txtDisplayHeight->setText(ssH.str());

	options1.newDisplayWidth = _res[_resCurrent]->w;
	options1.newDisplayHeight = _res[_resCurrent]->h;
}

/**
 * Changes the Display Width option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::txtDisplayWidthChange(Action *)
{
	std::stringstream ss;
	int width = 0;
	ss << std::dec << _txtDisplayWidth->getText();
	ss >> std::dec >> width;
	options1.newDisplayWidth = width;
	// Update resolution mode
	if (_res != (SDL_Rect**)-1 && _res != (SDL_Rect**)0)
	{
		int i;
		_resCurrent = -1;
		for (i = 0; _res[i]; ++i)
		{
			if (_resCurrent == -1 &&
				((_res[i]->w == options1.newDisplayWidth && _res[i]->h <= options1.newDisplayHeight) || _res[i]->w < options1.newDisplayWidth))
			{
				_resCurrent = i;
			}
		}
	}
}

/**
 * Changes the Display Height option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::txtDisplayHeightChange(Action *)
{
	std::stringstream ss;
	int height = 0;
	ss << std::dec << _txtDisplayHeight->getText();
	ss >> std::dec >> height;
	options1.newDisplayHeight = height;
	// Update resolution mode
	if (_res != (SDL_Rect**)-1 && _res != (SDL_Rect**)0)
	{
		int i;
		_resCurrent = -1;
		for (i = 0; _res[i]; ++i)
		{
			if (_resCurrent == -1 &&
				((_res[i]->w == options1.newDisplayWidth && _res[i]->h <= options1.newDisplayHeight) || _res[i]->w < options1.newDisplayWidth))
			{
				_resCurrent = i;
			}
		}
	}
}

/**
 * Changes the Language option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::cbxLanguageChange(Action *)
{
    options1.setlanguage(QString::fromStdString(_langs[_cbxLanguage->getSelected()]));
}

/**
 * Changes the Filter options.
 * @param action Pointer to an action.
 */
void OptionsVideoState::cbxFilterChange(Action *)
{
	switch (_cbxFilter->getSelected())
	{
	case 0:
		options1.newOpenGL = false;
		options1.newScaleFilter = false;
		options1.newHQXFilter = false;
		options1.newXBRZFilter = false;
		break;
	case 1:
		options1.newOpenGL = false;
		options1.newScaleFilter = true;
		options1.newHQXFilter = false;
		options1.newXBRZFilter = false;
		break;
	case 2:
		options1.newOpenGL = false;
		options1.newScaleFilter = false;
		options1.newHQXFilter = true;
		options1.newXBRZFilter = false;
		break;
	case 3:
		options1.newOpenGL = false;
		options1.newScaleFilter = false;
		options1.newHQXFilter = false;
		options1.newXBRZFilter = true;
		break;
	default:
		options1.newOpenGL = true;
		options1.newScaleFilter = false;
		options1.newHQXFilter = false;
		options1.newXBRZFilter = false;
		options1.newOpenGLShader = QString::fromStdString(_filters[_cbxFilter->getSelected()]);
		break;
	}
}

/**
 * Changes the Display Mode options.
 * @param action Pointer to an action.
 */
void OptionsVideoState::updateDisplayMode(Action *)
{
	switch(_cbxDisplayMode->getSelected())
	{
	case 0:
		options1.newFullscreen = false;
		options1.newBorderless = false;
		options1.newAllowResize = false;
		break;
	case 1:
		options1.newFullscreen = true;
		options1.newBorderless = false;
		options1.newAllowResize = false;
		break;
	case 2:
		options1.newFullscreen = false;
		options1.newBorderless = true;
		options1.newAllowResize = false;
		break;
	case 3:
		options1.newFullscreen = false;
		options1.newBorderless = false;
		options1.newAllowResize = true;
		break;
	default:
		break;
	}
}

/**
 * Changes the Letterboxing option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnLetterboxClick(Action *)
{
    options1.setkeepAspectRatio(_btnLetterbox->getPressed());
}

/**
 * Changes the Lock Mouse option.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnLockMouseClick(Action *)
{
	options1.setcaptureMouse((SDL_GrabMode)_btnLockMouse->getPressed());
	SDL_WM_GrabInput(SDL_GrabMode(options1.captureMouse()));
}

/**
 * Ask user where he wants to root screen.
 * @param action Pointer to an action.
 */
void OptionsVideoState::btnRootWindowedModeClick(Action *)
{
	if (_btnRootWindowedMode->getPressed())
	{
		game.pushState(new SetWindowedRootState(_origin, this));
	}
	else
	{
		options1.newRootWindowedMode = false;
	}
}

/**
 * Changes the geoscape scale.
 * @param action Pointer to an action.
 */
void OptionsVideoState::updateGeoscapeScale(Action *)
{
    options1.newGeoscapeScale = _reverseScales[_cbxGeoScale->getSelected()];
}

/**
 * Updates the Battlescape scale.
 * @param action Pointer to an action.
 */
void OptionsVideoState::updateBattlescapeScale(Action *)
{
    options1.newBattlescapeScale = _reverseScales[_cbxBattleScale->getSelected()];
}

/**
 * Updates the scale.
 * @param dX delta of X;
 * @param dY delta of Y;
 */
void OptionsVideoState::resize(int &dX, int &dY)
{
	OptionsBaseState::resize(dX, dY);
	std::ostringstream ss;
	ss << options1.displayWidth();
	_txtDisplayWidth->setText(ss.str());
	ss.str("");
	ss << options1.displayHeight();
	_txtDisplayHeight->setText(ss.str());
}

/**
 * Takes care of any events from the core game engine.
 * @param action Pointer to an action.
 */
void OptionsVideoState::handle(Action *action)
{
	State::handle(action);
	if (action->getDetails()->type == SDL_KEYDOWN && action->getDetails()->key.keysym.sym == SDLK_g && game.isCtrlPressed())
	{
		_btnLockMouse->setPressed(options1.captureMouse() == SDL_GRAB_ON);
	}
}

/**
 * Unpresses Fixed Borderless Pos button
 */
void OptionsVideoState::unpressRootWindowedMode()
{
	_btnRootWindowedMode->setPressed(false);
}

}
