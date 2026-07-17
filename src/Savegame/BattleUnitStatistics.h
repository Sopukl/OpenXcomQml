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
#include "BattleUnit.h"

namespace OpenXcom
{
/**
 * Container for battle unit kills statistics.
 */
	struct BattleUnitKills
{
	// Variables
	std::string name;
	std::string type, rank, race, weapon, weaponAmmo;
	UnitFaction faction;
	UnitStatus status;
	int mission, turn, id;
	UnitSide side;
	UnitBodyPart bodypart;

	// Functions
	/// Make turn unique across all kills
	int makeTurnUnique();

	/// Check to see if turn was on HOSTILE side
	bool hostileTurn() const;

	/// Make turn unique across mission
	void setTurn(int unitTurn, UnitFaction unitFaction);

	/// Load
	void load(const YAML::YamlNodeReader& reader);

	/// Save
	void save(YAML::YamlNodeWriter writer) const;

	/// Convert kill Status to string.
	std::string getKillStatusString() const;

	/// Convert victim Status to string.
	std::string getUnitStatusString() const;

	/// Convert victim Faction to string.
	std::string getUnitFactionString() const;

	/// Convert victim Side to string.
	std::string getUnitSideString() const;

	/// Convert victim Body part to string.
	std::string getUnitBodyPartString() const;

	/// Get human-readable victim name.
	std::string getUnitName() const;

	/// Decide victim name, race and rank.
	void setUnitStats(BattleUnit *unit);

	BattleUnitKills(const YAML::YamlNodeReader& reader) { load(reader); }
	BattleUnitKills(): faction(FACTION_HOSTILE), status(STATUS_IGNORE_ME), mission(0), turn(0), id(0), side(SIDE_FRONT), bodypart(BODYPART_HEAD) { }
	~BattleUnitKills() { }
};

/**
 * Container for battle unit statistics.
 */
	struct BattleUnitStatistics
{
	// Variables
	bool wasUnconcious;                  ///< Tracks if the soldier fell unconscious
	int shotAtCounter;                   ///< Tracks how many times the unit was shot at
	int hitCounter;                      ///< Tracks how many times the unit was hit
	int shotByFriendlyCounter;           ///< Tracks how many times the unit was hit by a friendly
	int shotFriendlyCounter;             ///< Tracks how many times the unit was hit a friendly
	bool loneSurvivor;                   ///< Tracks if the soldier was the only survivor
	bool ironMan;                        ///< Tracks if the soldier was the only soldier on the mission
	int longDistanceHitCounter;          ///< Tracks how many long distance shots were landed
	int lowAccuracyHitCounter;           ///< Tracks how many times the unit landed a low probability shot
	int shotsFiredCounter;               ///< Tracks how many times a unit has shot
	int shotsLandedCounter;              ///< Tracks how many times a unit has hit his target
	std::vector<BattleUnitKills*> kills; ///< Tracks kills
	int daysWounded;                     ///< Tracks how many days the unit was wounded for
	bool KIA;                            ///< Tracks if the soldier was killed in battle
	bool nikeCross;                      ///< Tracks if a soldier killed every alien or killed and stunned every alien
	bool mercyCross;                     ///< Tracks if a soldier stunned every alien
	int woundsHealed;                    ///< Tracks how many times a fatal wound was healed by this unit
	UnitStats delta;                     ///< Tracks the increase in unit stats (is not saved, only used during debriefing)
	int appliedStimulant;                ///< Tracks how many times this soldier applied stimulant
	int appliedPainKill;                 ///< Tracks how many times this soldier applied pain killers
	int revivedSoldier;                  ///< Tracks how many times this soldier revived another soldier
	int revivedHostile;                  ///< Tracks how many times this soldier revived another hostile
	int revivedNeutral;                  ///< Tracks how many times this soldier revived another civilian
	bool MIA;                            ///< Tracks if the soldier was left behind :(
	int martyr;                          ///< Tracks how many kills the soldier landed on the turn of his death
	int slaveKills;                      ///< Tracks how many kills the soldier landed thanks to a mind controlled unit.

	// Functions
	/// Duplicate entry check
	bool duplicateEntry(UnitStatus status, int id) const;

	/// Friendly fire check
	bool hasFriendlyFired() const;

	/// Load function
	void load(const YAML::YamlNodeReader& node);

	/// Save function
	void save(YAML::YamlNodeWriter writer) const;

	BattleUnitStatistics(const YAML::YamlNodeReader& reader) { load(reader); }
	BattleUnitStatistics() : wasUnconcious(false), shotAtCounter(0), hitCounter(0), shotByFriendlyCounter(0), shotFriendlyCounter(0), loneSurvivor(false), ironMan(false), longDistanceHitCounter(0), lowAccuracyHitCounter(0), shotsFiredCounter(0), shotsLandedCounter(0), kills(), daysWounded(0), KIA(false), nikeCross(false), mercyCross(false), woundsHealed(0), appliedStimulant(0), appliedPainKill(0), revivedSoldier(0), revivedHostile(0), revivedNeutral(0), MIA(false), martyr(0), slaveKills(0) { }
	~BattleUnitStatistics() { }
};
}
