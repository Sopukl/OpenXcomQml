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
#include "../Engine/Yaml.h"
#include "GameTime.h"
#include "../Mod/Mod.h"

namespace OpenXcom
{

/**
 * Container for mission statistics.
 */
struct MissionStatistics
{
	// Variables
	int id;
	std::string markerName;
	int markerId;
	GameTime time;
	std::string region, country, type, ufo;
	bool success;
	std::string rating;
	int score;
	std::string alienRace;
	int daylight;
	std::map<int, int> injuryList;
	bool valiantCrux;
	int lootValue;

	/// Load
	void load(const YAML::YamlNodeReader& reader);

	/// Save
	void save(YAML::YamlNodeWriter writer) const;

	std::string getMissionName() const;

	std::string getRatingString() const;

	std::string getLocationString() const;

	bool isDarkness(const Mod* mod) const;

	std::string getDaylightString(const Mod* mod) const;

	bool isAlienBase() const;

	bool isBaseDefense() const;

	bool isUfoMission() const;

	MissionStatistics(const YAML::YamlNodeReader& reader) : time(0, 0, 0, 0, 0, 0, 0) { load(reader); }
	MissionStatistics() : id(0), markerId(0), time(0, 0, 0, 0, 0, 0, 0), region("STR_REGION_UNKNOWN"), country("STR_UNKNOWN"), ufo("NO_UFO"), success(false), score(0), alienRace("STR_UNKNOWN"), daylight(0), valiantCrux(false), lootValue(0) { }
	~MissionStatistics() { }
};

}
