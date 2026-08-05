#include "MissionStatistics.h"

#include "../Engine/Game.h"

namespace OpenXcom
{

void MissionStatistics::load(const YAML::YamlNodeReader &reader)
{
	reader.tryRead("id", id);
	reader.tryRead("markerName", markerName);
	reader.tryRead("markerId", markerId);
	time.load(reader["time"]);
	reader.tryRead("region", region);
	reader.tryRead("country", country);
	reader.tryRead("type", type);
	reader.tryRead("ufo", ufo);
	reader.tryRead("success", success);
	reader.tryRead("score", score);
	reader.tryRead("rating", rating);
	reader.tryRead("alienRace", alienRace);
	reader.tryRead("daylight", daylight);
	reader.tryRead("injuryList", injuryList);
	reader.tryRead("valiantCrux", valiantCrux);
	reader.tryRead("lootValue", lootValue);
}

void MissionStatistics::save(YAML::YamlNodeWriter writer) const
{
	writer.setAsMap();
	writer.write("id", id);
	if (!markerName.empty())
	{
		writer.write("markerName", markerName);
		writer.write("markerId", markerId);
	}
	time.save(writer["time"]);
	writer.write("region", region);
	writer.write("country", country);
	writer.write("type", type);
	writer.write("ufo", ufo);
	writer.write("success", success);
	writer.write("score", score);
	writer.write("rating", rating);
	writer.write("alienRace", alienRace);
	writer.write("daylight", daylight);
	if (!injuryList.empty())
		writer.write("injuryList", injuryList);
	if (valiantCrux) writer.write("valiantCrux", valiantCrux);
	if (lootValue) writer.write("lootValue", lootValue);
}

std::string MissionStatistics::getMissionName() const
{
	Language *lang = game.language();
	if (!markerName.empty())
	{
		return lang->getString(markerName).arg(markerId);
	}
	else
	{
		return lang->getString(type);
	}
}

std::string MissionStatistics::getRatingString() const
{
	Language *lang = game.language();
	std::ostringstream ss;
	if (success)
	{
		ss << lang->getString("STR_VICTORY");
	}
	else
	{
		ss << lang->getString("STR_DEFEAT");
	}
	ss << " - " << lang->getString(rating);
	return ss.str();
}

std::string MissionStatistics::getLocationString() const
{
	if (country == "STR_UNKNOWN")
	{
		return region;
	}
	else
	{
		return country;
	}
}

bool MissionStatistics::isDarkness(const Mod *mod) const
{
	return daylight > mod->getMaxDarknessToSeeUnits();
}

std::string MissionStatistics::getDaylightString(const Mod *mod) const
{
	if (isDarkness(mod))
	{
		return "STR_NIGHT";
	}
	else
	{
		return "STR_DAY";
	}
}

bool MissionStatistics::isAlienBase() const
{
	if (type.find("STR_ALIEN_BASE") != std::string::npos || type.find("STR_ALIEN_COLONY") != std::string::npos)
	{
		return true;
	}
	return false;
}

bool MissionStatistics::isBaseDefense() const
{
	return (type == "STR_BASE_DEFENSE");
}

bool MissionStatistics::isUfoMission() const
{
	return !(ufo == "NO_UFO");
}

}