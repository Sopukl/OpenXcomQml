#include "BattleUnitStatistics.h"

#include <string>
#include <sstream>
#include "../Engine/Yaml.h"
#include "../Engine/Game.h"

namespace OpenXcom
{
	int BattleUnitKills::makeTurnUnique()
	{
		return turn += mission * 300; // Maintains divisibility by 3 as well
	}

	bool BattleUnitKills::hostileTurn() const
	{
		if ((turn - 1) % 3 == 0) return true;
		return false;
	}

	void BattleUnitKills::setTurn(int unitTurn, UnitFaction unitFaction)
	{
		turn = unitTurn * 3 + (int)unitFaction;
	}

	void BattleUnitKills::load(const YAML::YamlNodeReader &reader)
	{
		reader.tryRead("type", type); // The ones killed are usually hostiles, so read this first
		if (type.empty())
			reader.tryRead("name", name); // Can't have both type and name at the same time
		reader.tryRead("rank", rank);
		reader.tryRead("race", race);
		reader.tryRead("weapon", weapon);
		reader.tryRead("weaponAmmo", weaponAmmo);
		reader.tryRead("status", status);
		reader.tryRead("faction", faction);
		reader.tryRead("mission", mission);
		reader.tryRead("turn", turn);
		reader.tryRead("side", side);
		reader.tryRead("bodypart", bodypart);
		reader.tryRead("id", id);
	}

	void BattleUnitKills::save(YAML::YamlNodeWriter writer) const
	{
		writer.setAsMap();
		writer.setFlowStyle();
		if (!name.empty())
			writer.write("name", name);
		if (!type.empty())
			writer.write("type", type);
		writer.write("rank", rank);
		writer.write("race", race);
		writer.write("weapon", weapon);
		writer.write("weaponAmmo", weaponAmmo);
		writer.write("status", status);
		writer.write("faction", faction);
		writer.write("mission", mission);
		writer.write("turn", turn);
		writer.write("side", side);
		writer.write("bodypart", bodypart);
		writer.write("id", id);
	}

	std::string BattleUnitKills::getKillStatusString() const
	{
		switch (status)
		{
		case STATUS_DEAD:           return "STR_KILLED";
		case STATUS_UNCONSCIOUS:    return "STR_STUNNED";
		case STATUS_PANICKING:		return "STR_PANICKED";
		case STATUS_TURNING:		return "STR_MINDCONTROLLED";
		default:                    return "status error";
		}
	}

	std::string BattleUnitKills::getUnitStatusString() const
	{
		switch (status)
		{
		case STATUS_DEAD:           return "STATUS_DEAD";
		case STATUS_UNCONSCIOUS:    return "STATUS_UNCONSCIOUS";
		case STATUS_PANICKING:		return "STATUS_PANICKING";
		case STATUS_TURNING:		return "STATUS_TURNING";
		default:                    return "status error";
		}
	}

	std::string BattleUnitKills::getUnitFactionString() const
	{
		switch (faction)
		{
		case FACTION_PLAYER:    return "FACTION_PLAYER";
		case FACTION_HOSTILE:   return "FACTION_HOSTILE";
		case FACTION_NEUTRAL:   return "FACTION_NEUTRAL";
		default:                return "faction error";
		}
	}

	std::string BattleUnitKills::getUnitSideString() const
	{
		switch (side)
		{
		case SIDE_FRONT:    return "SIDE_FRONT";
		case SIDE_LEFT:     return "SIDE_LEFT";
		case SIDE_RIGHT:    return "SIDE_RIGHT";
		case SIDE_REAR:     return "SIDE_REAR";
		case SIDE_UNDER:    return "SIDE_UNDER";
		default:            return "side error";
		}
	}

	std::string BattleUnitKills::getUnitBodyPartString() const
	{
		switch (bodypart)
		{
		case BODYPART_HEAD:     return "BODYPART_HEAD";
		case BODYPART_TORSO:    return "BODYPART_TORSO";
		case BODYPART_RIGHTARM: return "BODYPART_RIGHTARM";
		case BODYPART_LEFTARM:  return "BODYPART_LEFTARM";
		case BODYPART_RIGHTLEG: return "BODYPART_RIGHTLEG";
		case BODYPART_LEFTLEG:  return "BODYPART_LEFTLEG";
		default:                return "body part error";
		}
	}

	std::string BattleUnitKills::getUnitName() const
	{
		Language *lang = game.getLanguage();
		if (!name.empty())
		{
			return name;
		}
		else if (!type.empty())
		{
			return lang->getString(type);
		}
		else
		{
			std::ostringstream ss;
			ss << lang << " " << lang->getString(rank);
			return ss.str();
		}
	}

	void BattleUnitKills::setUnitStats(BattleUnit *unit)
	{
		name = "";
		type = "";
		if (unit->getGeoscapeSoldier())
		{
			name = unit->getGeoscapeSoldier()->getName();
		}
		else
		{
			type = unit->getType();
		}

		if (unit->getOriginalFaction() == FACTION_PLAYER)
		{
			// Soldiers
			if (unit->getGeoscapeSoldier())
			{
				if (!unit->getGeoscapeSoldier()->getRankString().empty())
				{
					rank = unit->getGeoscapeSoldier()->getRankString();
				}
				else
				{
					rank = "STR_SOLDIER";
				}
				if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRace().empty())
				{
					race = unit->getUnitRules()->getRace();
				}
				else
				{
					race = "STR_FRIENDLY";
				}
			}
			// HWPs
			else
			{
				if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRank().empty())
				{
					rank = unit->getUnitRules()->getRank();
				}
				else
				{
					rank = "STR_HWPS";
				}
				if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRace().empty())
				{
					race = unit->getUnitRules()->getRace();
				}
				else
				{
					race = "STR_FRIENDLY";
				}
			}
		}
		// Aliens
		else if (unit->getOriginalFaction() == FACTION_HOSTILE)
		{
			if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRank().empty())
			{
				rank = unit->getUnitRules()->getRank();
			}
			else
			{
				rank = "STR_LIVE_SOLDIER";
			}
			if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRace().empty())
			{
				race = unit->getUnitRules()->getRace();
			}
			else
			{
				race = "STR_HOSTILE";
			}
		}
		// Civilians
		else if (unit->getOriginalFaction() == FACTION_NEUTRAL)
		{
			if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRank().empty())
			{
				rank = unit->getUnitRules()->getRank();
			}
			else
			{
				rank = "STR_CIVILIAN";
			}
			if (unit->getUnitRules() != 0 && !unit->getUnitRules()->getRace().empty())
			{
				race = unit->getUnitRules()->getRace();
			}
			else
			{
				race = "STR_NEUTRAL";
			}
		}
		// Error
		else
		{
			rank = "STR_UNKNOWN";
			race = "STR_UNKNOWN";
		}
	}

	bool BattleUnitStatistics::duplicateEntry(UnitStatus status, int id) const
	{
		for (const auto* buk : kills)
		{
			if (buk->id == id && buk->status == status)
			{
				return true;
			}
		}
		return false;
	}

	bool BattleUnitStatistics::hasFriendlyFired() const
	{
		for (const auto* buk : kills)
		{
			if (buk->faction == FACTION_PLAYER)
				return true;
		}
		return false;
	}

	void BattleUnitStatistics::load(const YAML::YamlNodeReader &node)
	{
		const auto& reader = node.useIndex();
		reader.tryRead("wasUnconcious", wasUnconcious);
		for (const auto& kill : reader["kills"].children())
			kills.push_back(new BattleUnitKills(kill));
		reader.tryRead("shotAtCounter", shotAtCounter);
		reader.tryRead("hitCounter", hitCounter);
		reader.tryRead("shotByFriendlyCounter", shotByFriendlyCounter);
		reader.tryRead("shotFriendlyCounter", shotFriendlyCounter);
		reader.tryRead("loneSurvivor", loneSurvivor);
		reader.tryRead("ironMan", ironMan);
		reader.tryRead("longDistanceHitCounter", longDistanceHitCounter);
		reader.tryRead("lowAccuracyHitCounter", lowAccuracyHitCounter);
		reader.tryRead("shotsFiredCounter", shotsFiredCounter);
		reader.tryRead("shotsLandedCounter", shotsLandedCounter);
		reader.tryRead("nikeCross", nikeCross);
		reader.tryRead("mercyCross", mercyCross);
		reader.tryRead("woundsHealed", woundsHealed);
		reader.tryRead("appliedStimulant", appliedStimulant);
		reader.tryRead("appliedPainKill", appliedPainKill);
		reader.tryRead("revivedSoldier", revivedSoldier);
		reader.tryRead("revivedHostile", revivedHostile);
		reader.tryRead("revivedNeutral", revivedNeutral);
		reader.tryRead("martyr", martyr);
		reader.tryRead("slaveKills", slaveKills);
	}

	void BattleUnitStatistics::save(YAML::YamlNodeWriter writer) const
	{
		writer.setAsMap();
		if (wasUnconcious) writer.write("wasUnconcious", wasUnconcious);
		writer.write("kills", kills,
					 [](YAML::YamlNodeWriter& w, BattleUnitKills* k)
					 { k->save(w.write()); });
		if (shotAtCounter) writer.write("shotAtCounter", shotAtCounter);
		if (hitCounter) writer.write("hitCounter", hitCounter);
		if (shotByFriendlyCounter) writer.write("shotByFriendlyCounter", shotByFriendlyCounter);
		if (shotFriendlyCounter) writer.write("shotFriendlyCounter", shotFriendlyCounter);
		if (loneSurvivor) writer.write("loneSurvivor", loneSurvivor);
		if (ironMan) writer.write("ironMan", ironMan);
		if (longDistanceHitCounter) writer.write("longDistanceHitCounter", longDistanceHitCounter);
		if (lowAccuracyHitCounter) writer.write("lowAccuracyHitCounter", lowAccuracyHitCounter);
		if (shotsFiredCounter) writer.write("shotsFiredCounter", shotsFiredCounter);
		if (shotsLandedCounter) writer.write("shotsLandedCounter", shotsLandedCounter);
		if (nikeCross) writer.write("nikeCross", nikeCross);
		if (mercyCross) writer.write("mercyCross", mercyCross);
		if (woundsHealed) writer.write("woundsHealed", woundsHealed);
		if (appliedStimulant) writer.write("appliedStimulant", appliedStimulant);
		if (appliedPainKill) writer.write("appliedPainKill", appliedPainKill);
		if (revivedSoldier) writer.write("revivedSoldier", revivedSoldier);
		if (revivedHostile) writer.write("revivedHostile", revivedHostile);
		if (revivedNeutral) writer.write("revivedNeutral", revivedNeutral);
		if (martyr) writer.write("martyr", martyr);
		if (slaveKills) writer.write("slaveKills", slaveKills);
		// for backwards compatibility, we output empty map as null
		if (!writer.toReader()[0])
		{
			writer.unsetAsMap();
			writer.setValueNull();
		}
	}

}
