#include "SoldierSortUtil.h"
#include "../Engine/Game.h"
#include "../Mod/RuleSoldier.h"

#define GET_ATTRIB_STAT_FN(attrib) \
	int OpenXcom::attrib##Stat(const Soldier *s) { return s->getStatsWithAllBonuses()->attrib; }
GET_ATTRIB_STAT_FN(tu)
GET_ATTRIB_STAT_FN(stamina)
GET_ATTRIB_STAT_FN(health)
GET_ATTRIB_STAT_FN(bravery)
GET_ATTRIB_STAT_FN(reactions)
GET_ATTRIB_STAT_FN(firing)
GET_ATTRIB_STAT_FN(throwing)
GET_ATTRIB_STAT_FN(strength)
int OpenXcom::manaStat(const Soldier* s)
{
	// don't reveal mana before it would otherwise be known
	if (game.savedGame()->isManaUnlocked(game.getMod()))
	{
		return s->getStatsWithAllBonuses()->mana;
	}
	return 0;
}
int OpenXcom::psiStrengthStat(const Soldier *s)
{
	// don't reveal psi strength before it would otherwise be known
	if (s->getCurrentStats()->psiSkill > 0
		|| (options1.psiStrengthEval()
		&& game.savedGame()->isResearched(game.getMod()->getPsiRequirements())))
	{
		return s->getStatsWithAllBonuses()->psiStrength;
	}
	return 0;
}
int OpenXcom::psiSkillStat(const Soldier *s)
{
	// when options1.anytimePsiTraining() is turned on, psiSkill can actually have a negative value
	if (s->getCurrentStats()->psiSkill > 0)
	{
		return s->getStatsWithAllBonuses()->psiSkill;
	}
	return 0;
}
GET_ATTRIB_STAT_FN(melee)
#undef GET_ATTRIB_STAT_FN

#define GET_ATTRIB_STAT_FN(attrib) \
	int OpenXcom::attrib##StatBase(const Soldier *s) { return s->getCurrentStats()->attrib; }
GET_ATTRIB_STAT_FN(tu)
GET_ATTRIB_STAT_FN(stamina)
GET_ATTRIB_STAT_FN(health)
GET_ATTRIB_STAT_FN(bravery)
GET_ATTRIB_STAT_FN(reactions)
GET_ATTRIB_STAT_FN(firing)
GET_ATTRIB_STAT_FN(throwing)
GET_ATTRIB_STAT_FN(strength)
int OpenXcom::manaStatBase(const Soldier* s)
{
	// don't reveal mana before it would otherwise be known
	if (game.savedGame()->isManaUnlocked(game.getMod()))
	{
		return s->getCurrentStats()->mana;
	}
	return 0;
}
int OpenXcom::psiStrengthStatBase(const Soldier *s)
{
	// don't reveal psi strength before it would otherwise be known
	if (s->getCurrentStats()->psiSkill > 0
		|| (options1.psiStrengthEval()
		&& game.savedGame()->isResearched(game.getMod()->getPsiRequirements())))
	{
		return s->getCurrentStats()->psiStrength;
	}
	return 0;
}
int OpenXcom::psiSkillStatBase(const Soldier *s)
{
	// when options1.anytimePsiTraining() is turned on, psiSkill can actually have a negative value
	if (s->getCurrentStats()->psiSkill > 0)
	{
		return s->getCurrentStats()->psiSkill;
	}
	return 0;
}
GET_ATTRIB_STAT_FN(melee)
#undef GET_ATTRIB_STAT_FN

#define GET_ATTRIB_STAT_FN(attrib) \
	int OpenXcom::attrib##StatPlus(const Soldier *s) { return s->getStatsWithSoldierBonusesOnly()->attrib; }
GET_ATTRIB_STAT_FN(tu)
GET_ATTRIB_STAT_FN(stamina)
GET_ATTRIB_STAT_FN(health)
GET_ATTRIB_STAT_FN(bravery)
GET_ATTRIB_STAT_FN(reactions)
GET_ATTRIB_STAT_FN(firing)
GET_ATTRIB_STAT_FN(throwing)
GET_ATTRIB_STAT_FN(strength)
int OpenXcom::manaStatPlus(const Soldier* s)
{
	// don't reveal mana before it would otherwise be known
	if (game.savedGame()->isManaUnlocked(game.getMod()))
	{
		return s->getStatsWithSoldierBonusesOnly()->mana;
	}
	return 0;
}
int OpenXcom::psiStrengthStatPlus(const Soldier *s)
{
	// don't reveal psi strength before it would otherwise be known
	if (s->getCurrentStats()->psiSkill > 0
		|| (options1.psiStrengthEval()
		&& game.savedGame()->isResearched(game.getMod()->getPsiRequirements())))
	{
		return s->getStatsWithSoldierBonusesOnly()->psiStrength;
	}
	return 0;
}
int OpenXcom::psiSkillStatPlus(const Soldier *s)
{
	// when options1.anytimePsiTraining() is turned on, psiSkill can actually have a negative value
	if (s->getCurrentStats()->psiSkill > 0)
	{
		return s->getStatsWithSoldierBonusesOnly()->psiSkill;
	}
	return 0;
}
GET_ATTRIB_STAT_FN(melee)
#undef GET_ATTRIB_STAT_FN


#define GET_SOLDIER_STAT_FN(attrib, camelCaseAttrib) \
	int OpenXcom::attrib##Stat(const Soldier *s) { return s->get##camelCaseAttrib(); }
GET_SOLDIER_STAT_FN(id, Id)
int OpenXcom::nameStat(const Soldier *s)
{
	return 0;
}
int OpenXcom::craftIdStat(const Soldier *s)
{
	if (s->getCraft())
	{
		return s->getCraft()->getId();
	}
	return 0;
}
int OpenXcom::typeStat(const Soldier *s)
{
	return s->getRules()->getListOrder();
}
GET_SOLDIER_STAT_FN(rank, Rank)
GET_SOLDIER_STAT_FN(missions, Missions)
GET_SOLDIER_STAT_FN(kills, Kills)
//GET_SOLDIER_STAT_FN(woundRecovery, WoundRecovery)
int OpenXcom::woundRecoveryStat(const Soldier *s)
{
	return s->getWoundRecovery(0.0f, 0.0f);
}
GET_SOLDIER_STAT_FN(manaMissing, ManaMissing)
int OpenXcom::idleDaysStat(const Soldier *s)
{
	return game.savedGame()->getSoldierIdleDays(s);
}
#undef GET_SOLDIER_STAT_FN
