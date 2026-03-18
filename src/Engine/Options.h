#pragma once
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
#include "Options1.h"
#include <string>
#include <vector>
#include "OptionInfo.h"
#include "ModInfo.h"

namespace OpenXcom
{

/**
 * Container for all the various global game options
 * and customizable settings.
 */
namespace Options
{
#define OPT extern
#include "Options.inc.h"
#undef OPT

	/// Creates the options info.
	void create();
	void createOptionsOXC();
	void createAdvancedOptionsOXC();
	void createControlsOXC();
	void createOptionsOXCE();
	void createAdvancedOptionsOXCE();
	void createControlsOXCE();
	void createOptionsOTHER();
	void createAdvancedOptionsOTHER();
	void createControlsOTHER();
	/// Restores default options.
	void resetDefault(bool includeMods);
	/// Initializes the options settings.
	bool init();
	/// Loads options from YAML.
	bool load(const std::string &filename = "options");
	/// Saves options to YAML.
	bool save(bool reset = false, const std::string &filename = "options");
	/// Gets the game's data folder.
	std::string getDataFolder();
	/// Sets the game's data folder.
	void setDataFolder(const std::string &folder);
	/// Gets the game's data list.
	const std::vector<std::string> &getDataList();
	/// Gets the game's user folder.
	std::string getUserFolder();
	/// Gets the game's config folder.
	std::string getConfigFolder();
	/// Gets the game's master mod user folder.
	std::string getMasterUserFolder();
	/// Gets the game's options.
	const std::vector<OptionInfo> &getOptionInfo();
	/// Sets the game's data, user and config folders.
	void setFolders();
	/// Update game options from config file and command line.
	void updateOptions();
	/// Backup display options.
	void backupDisplay();
	/// Switches display options.
	void switchDisplay();
	/// Is the password correct?
	bool isPasswordCorrect();
	/// returns the id of the active master mod
	std::string getActiveMaster();
	/// Gets the master mod info.
	const ModInfo* getActiveMasterInfo();
	/// Gets the xcom ruleset info.
	const ModInfo* getXcomRulesetInfo();
	/// Gets the map of mod ids to mod infos
	const std::map<std::string, ModInfo> &getModInfos();
	/// Refreshes the mods.
	void refreshMods();
	/// Refreshes the mods and filemaps.
	void updateMods();
	/// Gets the list of currently active mods.
	std::vector<const ModInfo*> getActiveMods();
	/// If we should skip the main menu and just load the last save
	bool getLoadLastSave();
	/// If we should skip the main menu and just load the specified save
	const std::string& getLoadThisSave();
	/// And do it only at startup
	void expendLoadLastSave();
}

}
