/*
 * Copyright 2010-2018 OpenXcom Developers.
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
#include "SoldierTransformationState.h"
#include "../Engine/Action.h"
#include "../Engine/Game.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Options.h"
#include "../Engine/Screen.h"
#include "../Interface/Text.h"
#include "../Interface/TextButton.h"
#include "../Interface/TextEdit.h"
#include "../Interface/TextList.h"
#include "../Interface/Window.h"
#include "../Mod/Mod.h"
#include "../Mod/RuleSoldier.h"
#include "../Mod/RuleSoldierBonus.h"
#include "../Mod/RuleSoldierTransformation.h"
#include "../Savegame/Base.h"
#include "../Savegame/ItemContainer.h"
#include "../Savegame/SavedGame.h"
#include "../Savegame/Soldier.h"
#include "../Savegame/Transfer.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Soldier Transformation GUI
 * @param transformationRule Pointer to the transformation ruleset
 * @param base Pointer to the current base
 * @param sourceSoldier Pointer to the selected soldier
 * @param filteredListOfSoldiers Pointer to the list of available soldiers
 */
SoldierTransformationState::SoldierTransformationState(RuleSoldierTransformation *transformationRule, Base *base, Soldier *sourceSoldier, std::vector<Soldier *> *filteredListOfSoldiers) :
	_transformationRule(transformationRule), _base(base), _sourceSoldier(sourceSoldier), _filteredListOfSoldiers(filteredListOfSoldiers)
{
	_window = new Window(this, 320, 200, 0, 0);
	_btnCancel = new TextButton(148, 16, 8, 176);
	_btnStart = new TextButton(148, 16, 164, 176);

	_btnLeftArrow = new TextButton(16, 16, 8, 8);
	_btnRightArrow = new TextButton(16, 16, 296, 8);
	_edtSoldier = new TextEdit(this, 210, 16, 54, 8);

	_txtCost = new Text(290, 9, 16, 30);
	_txtTransferTime = new Text(290, 9, 16, 40);
	_txtRecoveryTime = new Text(290, 9, 16, 50);

	_txtRequiredItems = new Text(290, 9, 16, 64);
	_txtItemNameColumn = new Text(60, 16, 30, 72);
	_txtUnitRequiredColumn = new Text(60, 16, 155, 72);
	_txtUnitAvailableColumn = new Text(60, 16, 230, 72);
	_lstRequiredItems = new TextList(270, 32, 30, 88);

	_lstStatChanges = new TextList(288, 40, 16, 130);

	// Set palette
	setInterface("soldierTransformation");

	add(_window, "window", "soldierTransformation");
	add(_btnCancel, "button", "soldierTransformation");
	add(_btnStart, "button", "soldierTransformation");

	add(_btnLeftArrow, "button", "soldierTransformation");
	add(_btnRightArrow, "button", "soldierTransformation");
	add(_edtSoldier, "text", "soldierTransformation");

	add(_txtCost, "text", "soldierTransformation");
	add(_txtTransferTime, "text", "soldierTransformation");
	add(_txtRecoveryTime, "text", "soldierTransformation");

	add(_txtRequiredItems, "text", "soldierTransformation");
	add(_txtItemNameColumn, "text", "soldierTransformation");
	add(_txtUnitRequiredColumn, "text", "soldierTransformation");
	add(_txtUnitAvailableColumn, "text", "soldierTransformation");
	add(_lstRequiredItems, "list1", "soldierTransformation");

	add(_lstStatChanges, "list2", "soldierTransformation");

	centerAllSurfaces();

	// Set up objects
	setWindowBackground(_window, "soldierTransformation");

	_btnCancel->setText(ltr("STR_CANCEL_UC"));
	_btnCancel->onMouseClick((ActionHandler)&SoldierTransformationState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&SoldierTransformationState::btnCancelClick, options1.keyCancel());

	_btnStart->setText(ltr(_transformationRule->getName()));
	_btnStart->onMouseClick((ActionHandler)&SoldierTransformationState::btnStartClick);
	_btnStart->onKeyboardPress((ActionHandler)&SoldierTransformationState::btnStartClick, options1.keyOk());

	if (_filteredListOfSoldiers && _filteredListOfSoldiers->size() > 1)
	{
		_btnLeftArrow->setText("<<");
		_btnLeftArrow->onMouseClick((ActionHandler)&SoldierTransformationState::btnLeftArrowClick);
		_btnLeftArrow->onKeyboardPress((ActionHandler)&SoldierTransformationState::btnLeftArrowClick, options1.keyGeoLeft());

		_btnRightArrow->setText(">>");
		_btnRightArrow->onMouseClick((ActionHandler)&SoldierTransformationState::btnRightArrowClick);
		_btnRightArrow->onKeyboardPress((ActionHandler)&SoldierTransformationState::btnRightArrowClick, options1.keyGeoRight());
	}
	else
	{
		_btnLeftArrow->setVisible(false);
		_btnRightArrow->setVisible(false);
	}

	_edtSoldier->setBig();
	_edtSoldier->setAlign(ALIGN_CENTER);

	_txtRequiredItems->setText(ltr("STR_SPECIAL_MATERIALS_REQUIRED"));
	_txtRequiredItems->setAlign(ALIGN_CENTER);

	_txtItemNameColumn->setText(ltr("STR_ITEM_REQUIRED"));
	_txtItemNameColumn->setWordWrap(true);

	_txtUnitRequiredColumn->setText(ltr("STR_UNITS_REQUIRED"));
	_txtUnitRequiredColumn->setWordWrap(true);

	_txtUnitAvailableColumn->setText(ltr("STR_UNITS_AVAILABLE"));
	_txtUnitAvailableColumn->setWordWrap(true);

	_lstRequiredItems->setColumns(3, 140, 75, 55);

	if (game.getMod()->isManaFeatureEnabled())
	{
		_lstStatChanges->setColumns(14, 72, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 0);
	}
	else
	{
		_lstStatChanges->setColumns(13, 90, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 0);
	}
	_lstStatChanges->setAlign(ALIGN_RIGHT);
	_lstStatChanges->setAlign(ALIGN_LEFT, 0);

	initTransformationData();
}

/**
 * cleans up dynamic state
 */
SoldierTransformationState::~SoldierTransformationState()
{

}

/**
 * Creates a string for the soldier stats table
 */
std::string SoldierTransformationState::formatStat(int stat, bool plus, bool hide)
{
	if (hide) return "\x01?\x01"; //Unicode::TOK_COLOR_FLIP
	if (stat == 0) return "";

	std::ostringstream ss;
	ss << Unicode::TOK_COLOR_FLIP;
	if (plus && stat > 0) ss << '+';
	ss << stat << Unicode::TOK_COLOR_FLIP;
	return ss.str();
}

/**
 * Sets all the values for the data fields on the screen
 */
void SoldierTransformationState::initTransformationData()
{
	_edtSoldier->setText(_sourceSoldier->getName());

	_lstRequiredItems->clearList();
	_lstStatChanges->clearList();

	bool transformationPossible = game.savedGame()->getFunds() >= _transformationRule->getCost();

	if (_base->getAvailableQuarters() <= _base->getUsedQuarters() &&
		(_transformationRule->isCreatingClone() ||
		(_transformationRule->isAllowingDeadSoldiers() && _sourceSoldier->getDeath())))
	{
		transformationPossible = false;
	}

	_txtCost->setText(ltr("STR_COST_").arg(Unicode::formatFunding(_transformationRule->getCost())));

	int transferTime = 0;
	if (!Mod::isEmptyRuleName(_transformationRule->getProducedItem()))
	{
		transferTime = _transformationRule->getTransferTime() > 0 ? _transformationRule->getTransferTime() : 1;
	}
	else if (_transformationRule->getTransferTime() > 0 || _transformationRule->isCreatingClone() || _sourceSoldier->getDeath())
	{
		transferTime = _transformationRule->getTransferTime() > 0 ? _transformationRule->getTransferTime() : 24;
	}
	_txtTransferTime->setText(ltr("STR_TRANSFER_TIME").arg(ltr("STR_HOUR", transferTime)));
	_txtRecoveryTime->setText(ltr("STR_RECOVERY_TIME").arg(ltr("STR_DAY", _transformationRule->getRecoveryTime())));

	int row = 0;
	for (auto& requiredItem : _transformationRule->getRequiredItems())
	{
		std::ostringstream s1, s2;
		s1 << requiredItem.second;
		const auto* rule = game.getMod()->getItem(requiredItem.first);
		if (rule != 0)
		{
			s2 << _base->getStorageItems().countOf(rule);
			transformationPossible &= (_base->getStorageItems().countOf(rule) >= requiredItem.second);
		}

		_lstRequiredItems->addRow(3, ltr(requiredItem.first).c_str(), s1.str().c_str(), s2.str().c_str());
		_lstRequiredItems->setCellColor(row, 1, _lstRequiredItems->getSecondaryColor());
		_lstRequiredItems->setCellColor(row, 2, _lstRequiredItems->getSecondaryColor());
		row++;
	}

	_btnStart->setVisible(transformationPossible);

	if (!Mod::isEmptyRuleName(_transformationRule->getProducedItem()))
	{
		_txtRecoveryTime->setVisible(false);

		// no need to show the rest, the soldier will be removed from existence after this project
		return;
	}

	UnitStats currentStats = *_sourceSoldier->getCurrentStats();
	UnitStats changedStatsMin = _sourceSoldier->calculateStatChanges(game.getMod(), _transformationRule, _sourceSoldier, 1, _sourceSoldier->getRules());
	UnitStats changedStatsMax = _sourceSoldier->calculateStatChanges(game.getMod(), _transformationRule, _sourceSoldier, 2, _sourceSoldier->getRules());
	UnitStats bonusStats;
	auto* bonusRule = game.getMod()->getSoldierBonus(_transformationRule->getSoldierBonusType(), false);
	if (bonusRule)
	{
		bonusStats += *bonusRule->getStats();
	}

	bool showPsiSkill = currentStats.psiSkill > 0;
	bool showPsiStrength = showPsiSkill || (options1.psiStrengthEval() && game.savedGame()->isResearched(game.getMod()->getPsiRequirements()));

	UnitStats rerollFlags = _transformationRule->getRerollStats();

	UnitStats randomFlags;
	bool twoRows = _transformationRule->getShowMinMax();
	if (!twoRows)
	{
		randomFlags += UnitStats::isRandom(_transformationRule->getFlatMin(), _transformationRule->getFlatMax());
		randomFlags += UnitStats::isRandom(_transformationRule->getPercentMin(), _transformationRule->getPercentMax());
		randomFlags += UnitStats::isRandom(_transformationRule->getPercentGainedMin(), _transformationRule->getPercentGainedMax());
	}

	if (game.getMod()->isManaFeatureEnabled())
	{
		bool showMana = game.savedGame()->isManaUnlocked(game.getMod());

		_lstStatChanges->addRow(14, "",
			ltr("STR_TIME_UNITS_ABBREVIATION").c_str(),
			ltr("STR_STAMINA_ABBREVIATION").c_str(),
			ltr("STR_HEALTH_ABBREVIATION").c_str(),
			ltr("STR_BRAVERY_ABBREVIATION").c_str(),
			ltr("STR_REACTIONS_ABBREVIATION").c_str(),
			ltr("STR_FIRING_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_THROWING_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_MELEE_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_STRENGTH_ABBREVIATION").c_str(),
			ltr("STR_MANA_ABBREVIATION").c_str(),
			ltr("STR_PSIONIC_STRENGTH_ABBREVIATION").c_str(),
			ltr("STR_PSIONIC_SKILL_ABBREVIATION").c_str(),
			"");
		_lstStatChanges->addRow(14, ltr("STR_CURRENT_STATS").c_str(),
			formatStat(currentStats.tu, false, false).c_str(),
			formatStat(currentStats.stamina, false, false).c_str(),
			formatStat(currentStats.health, false, false).c_str(),
			formatStat(currentStats.bravery, false, false).c_str(),
			formatStat(currentStats.reactions, false, false).c_str(),
			formatStat(currentStats.firing, false, false).c_str(),
			formatStat(currentStats.throwing, false, false).c_str(),
			formatStat(currentStats.melee, false, false).c_str(),
			formatStat(currentStats.strength, false, false).c_str(),
			formatStat(currentStats.mana, false, !showMana).c_str(),
			formatStat(currentStats.psiStrength, false, !showPsiStrength).c_str(),
			formatStat(currentStats.psiSkill, false, !showPsiSkill).c_str(),
			"");
		_lstStatChanges->addRow(14, ltr(twoRows ? "STR_CHANGES_MIN" : "STR_CHANGES").c_str(),
			formatStat(changedStatsMin.tu, true, rerollFlags.tu || randomFlags.tu).c_str(),
			formatStat(changedStatsMin.stamina, true, rerollFlags.stamina || randomFlags.stamina).c_str(),
			formatStat(changedStatsMin.health, true, rerollFlags.health || randomFlags.health).c_str(),
			formatStat(changedStatsMin.bravery, true, rerollFlags.bravery || randomFlags.bravery).c_str(),
			formatStat(changedStatsMin.reactions, true, rerollFlags.reactions || randomFlags.reactions).c_str(),
			formatStat(changedStatsMin.firing, true, rerollFlags.firing || randomFlags.firing).c_str(),
			formatStat(changedStatsMin.throwing, true, rerollFlags.throwing || randomFlags.throwing).c_str(),
			formatStat(changedStatsMin.melee, true, rerollFlags.melee || randomFlags.melee).c_str(),
			formatStat(changedStatsMin.strength, true, rerollFlags.strength || randomFlags.strength).c_str(),
			formatStat(changedStatsMin.mana, true, !showMana || rerollFlags.mana || randomFlags.mana).c_str(),
			formatStat(changedStatsMin.psiStrength, true, !showPsiStrength || rerollFlags.psiStrength || randomFlags.psiStrength).c_str(),
			formatStat(changedStatsMin.psiSkill, true, !showPsiSkill || rerollFlags.psiSkill || randomFlags.psiSkill).c_str(),
			"");
		if (twoRows)
		{
			_lstStatChanges->addRow(14, ltr("STR_CHANGES_MAX").c_str(),
				formatStat(changedStatsMax.tu, true, rerollFlags.tu).c_str(),
				formatStat(changedStatsMax.stamina, true, rerollFlags.stamina).c_str(),
				formatStat(changedStatsMax.health, true, rerollFlags.health).c_str(),
				formatStat(changedStatsMax.bravery, true, rerollFlags.bravery).c_str(),
				formatStat(changedStatsMax.reactions, true, rerollFlags.reactions).c_str(),
				formatStat(changedStatsMax.firing, true, rerollFlags.firing).c_str(),
				formatStat(changedStatsMax.throwing, true, rerollFlags.throwing).c_str(),
				formatStat(changedStatsMax.melee, true, rerollFlags.melee).c_str(),
				formatStat(changedStatsMax.strength, true, rerollFlags.strength).c_str(),
				formatStat(changedStatsMax.mana, true, !showMana || rerollFlags.mana).c_str(),
				formatStat(changedStatsMax.psiStrength, true, !showPsiStrength || rerollFlags.psiStrength).c_str(),
				formatStat(changedStatsMax.psiSkill, true, !showPsiSkill || rerollFlags.psiSkill).c_str(),
				"");
		}
		if (bonusRule)
		{
			_lstStatChanges->addRow(14, ltr("STR_BONUS_STATS").c_str(),
				formatStat(bonusStats.tu, true, false).c_str(),
				formatStat(bonusStats.stamina, true, false).c_str(),
				formatStat(bonusStats.health, true, false).c_str(),
				formatStat(bonusStats.bravery, true, false).c_str(),
				formatStat(bonusStats.reactions, true, false).c_str(),
				formatStat(bonusStats.firing, true, false).c_str(),
				formatStat(bonusStats.throwing, true, false).c_str(),
				formatStat(bonusStats.melee, true, false).c_str(),
				formatStat(bonusStats.strength, true, false).c_str(),
				formatStat(bonusStats.mana, true, false).c_str(),
				formatStat(bonusStats.psiStrength, true, false).c_str(),
				formatStat(bonusStats.psiSkill, true, false).c_str(),
				"");
		}
	}
	else
	{
		_lstStatChanges->addRow(13, "",
			ltr("STR_TIME_UNITS_ABBREVIATION").c_str(),
			ltr("STR_STAMINA_ABBREVIATION").c_str(),
			ltr("STR_HEALTH_ABBREVIATION").c_str(),
			ltr("STR_BRAVERY_ABBREVIATION").c_str(),
			ltr("STR_REACTIONS_ABBREVIATION").c_str(),
			ltr("STR_FIRING_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_THROWING_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_MELEE_ACCURACY_ABBREVIATION").c_str(),
			ltr("STR_STRENGTH_ABBREVIATION").c_str(),
			ltr("STR_PSIONIC_STRENGTH_ABBREVIATION").c_str(),
			ltr("STR_PSIONIC_SKILL_ABBREVIATION").c_str(),
			"");
		_lstStatChanges->addRow(13, ltr("STR_CURRENT_STATS").c_str(),
			formatStat(currentStats.tu, false, false).c_str(),
			formatStat(currentStats.stamina, false, false).c_str(),
			formatStat(currentStats.health, false, false).c_str(),
			formatStat(currentStats.bravery, false, false).c_str(),
			formatStat(currentStats.reactions, false, false).c_str(),
			formatStat(currentStats.firing, false, false).c_str(),
			formatStat(currentStats.throwing, false, false).c_str(),
			formatStat(currentStats.melee, false, false).c_str(),
			formatStat(currentStats.strength, false, false).c_str(),
			formatStat(currentStats.psiStrength, false, !showPsiStrength).c_str(),
			formatStat(currentStats.psiSkill, false, !showPsiSkill).c_str(),
			"");
		_lstStatChanges->addRow(13, ltr(twoRows ? "STR_CHANGES_MIN" : "STR_CHANGES").c_str(),
			formatStat(changedStatsMin.tu, true, rerollFlags.tu || randomFlags.tu).c_str(),
			formatStat(changedStatsMin.stamina, true, rerollFlags.stamina || randomFlags.stamina).c_str(),
			formatStat(changedStatsMin.health, true, rerollFlags.health || randomFlags.health).c_str(),
			formatStat(changedStatsMin.bravery, true, rerollFlags.bravery || randomFlags.bravery).c_str(),
			formatStat(changedStatsMin.reactions, true, rerollFlags.reactions || randomFlags.reactions).c_str(),
			formatStat(changedStatsMin.firing, true, rerollFlags.firing || randomFlags.firing).c_str(),
			formatStat(changedStatsMin.throwing, true, rerollFlags.throwing || randomFlags.throwing).c_str(),
			formatStat(changedStatsMin.melee, true, rerollFlags.melee || randomFlags.melee).c_str(),
			formatStat(changedStatsMin.strength, true, rerollFlags.strength || randomFlags.strength).c_str(),
			formatStat(changedStatsMin.psiStrength, true, !showPsiStrength || rerollFlags.psiStrength || randomFlags.psiStrength).c_str(),
			formatStat(changedStatsMin.psiSkill, true, !showPsiSkill || rerollFlags.psiSkill || randomFlags.psiSkill).c_str(),
			"");
		if (twoRows)
		{
			_lstStatChanges->addRow(13, ltr("STR_CHANGES").c_str(),
				formatStat(changedStatsMax.tu, true, rerollFlags.tu).c_str(),
				formatStat(changedStatsMax.stamina, true, rerollFlags.stamina).c_str(),
				formatStat(changedStatsMax.health, true, rerollFlags.health).c_str(),
				formatStat(changedStatsMax.bravery, true, rerollFlags.bravery).c_str(),
				formatStat(changedStatsMax.reactions, true, rerollFlags.reactions).c_str(),
				formatStat(changedStatsMax.firing, true, rerollFlags.firing).c_str(),
				formatStat(changedStatsMax.throwing, true, rerollFlags.throwing).c_str(),
				formatStat(changedStatsMax.melee, true, rerollFlags.melee).c_str(),
				formatStat(changedStatsMax.strength, true, rerollFlags.strength).c_str(),
				formatStat(changedStatsMax.psiStrength, true, !showPsiStrength || rerollFlags.psiStrength).c_str(),
				formatStat(changedStatsMax.psiSkill, true, !showPsiSkill || rerollFlags.psiSkill).c_str(),
				"");
		}
		if (bonusRule)
		{
			_lstStatChanges->addRow(13, ltr("STR_BONUS_STATS").c_str(),
				formatStat(bonusStats.tu, true, false).c_str(),
				formatStat(bonusStats.stamina, true, false).c_str(),
				formatStat(bonusStats.health, true, false).c_str(),
				formatStat(bonusStats.bravery, true, false).c_str(),
				formatStat(bonusStats.reactions, true, false).c_str(),
				formatStat(bonusStats.firing, true, false).c_str(),
				formatStat(bonusStats.throwing, true, false).c_str(),
				formatStat(bonusStats.melee, true, false).c_str(),
				formatStat(bonusStats.strength, true, false).c_str(),
				formatStat(bonusStats.psiStrength, true, false).c_str(),
				formatStat(bonusStats.psiSkill, true, false).c_str(),
				"");
		}
	}
}

/**
 * Returns to previous screen.
 * @param action A pointer to an Action.
 */
void SoldierTransformationState::btnCancelClick(Action *action)
{
	game.popState();
}

/**
 * Performs the selected transformation on the selected soldier
 * @param action A pointer to an Action.
 */
void SoldierTransformationState::btnStartClick(Action *action)
{
	// Pay upfront, no refunds
	game.savedGame()->setFunds(game.savedGame()->getFunds() - _transformationRule->getCost());

	for (auto& requiredItem : _transformationRule->getRequiredItems())
	{
		const auto* rule = game.getMod()->getItem(requiredItem.first);
		if (rule != 0)
		{
			_base->getStorageItems().removeItem(rule, requiredItem.second);
		}
	}

	// Generate an event (side effect)
	const std::string choice = _transformationRule->chooseEvent();
	if (!choice.empty())
	{
		RuleEvent* eventToSpawn = game.getMod()->getEvent(choice, false);
		if (eventToSpawn)
		{
			game.savedGame()->spawnEvent(eventToSpawn);
		}
	}

	// Here we go
	if (!Mod::isEmptyRuleName(_transformationRule->getProducedItem()))
	{
		retire();
	}
	else
	{
		performTransformation();
	}

	game.popState();
}

void SoldierTransformationState::performTransformation()
{
	Soldier *destinationSoldier = 0;

	if (_transformationRule->isCreatingClone())
	{
		int newId = game.savedGame()->getId("STR_SOLDIER");
		RuleSoldier *newSoldierType = game.getMod()->getSoldier(_sourceSoldier->getRules()->getType());
		if (!Mod::isEmptyRuleName(_transformationRule->getProducedSoldierType()))
		{
			newSoldierType = game.getMod()->getSoldier(_transformationRule->getProducedSoldierType());
		}
		destinationSoldier = new Soldier(
			newSoldierType,
			newSoldierType->getDefaultArmor(),
			_sourceSoldier->getNationality(), // try to preserve nationality if possible
			newId);

		// copy stuff that is not influenced by transformation ruleset
		destinationSoldier->setGender(_sourceSoldier->getGender());
		destinationSoldier->setLook(_sourceSoldier->getLook());
		destinationSoldier->setLookVariant(_sourceSoldier->getLookVariant());

		// preserve nationality only for soldiers of the same type
		if (_sourceSoldier->getRules() == newSoldierType)
		{
			destinationSoldier->setNationality(_sourceSoldier->getNationality());
		}

		// allow easy name handling when cloning (e.g. John Doe III => John Doe IV)
		destinationSoldier->setName(_edtSoldier->getText());
	}
	else
	{
		destinationSoldier = _sourceSoldier;

		// some players want to rename soldiers too
		destinationSoldier->setName(_edtSoldier->getText());

		if (_sourceSoldier->getDeath())
		{
			// true resurrect = remove from Memorial Wall
			auto it = find(game.savedGame()->getDeadSoldiers().begin(), game.savedGame()->getDeadSoldiers().end(), _sourceSoldier);
			if (it != game.savedGame()->getDeadSoldiers().end())
			{
				game.savedGame()->getDeadSoldiers().erase(it);
			}
		}
		else if (_transformationRule->getTransferTime() > 0)
		{
			// transfer time on a live soldier already at the base (doesn't make much sense, but we need to handle it anyway)
			auto it = find(_base->soldiers().begin(), _base->soldiers().end(), _sourceSoldier);
			if (it != _base->soldiers().end())
			{
				_base->soldiers().erase(it);
			}
		}
	}

	if (_transformationRule->getTransferTime() > 0 || _transformationRule->isCreatingClone() || _sourceSoldier->getDeath())
	{
		// handle training (transfer rules)
		destinationSoldier->setPsiTraining(false);
		if (destinationSoldier->isInTraining())
		{
			destinationSoldier->setReturnToTrainingWhenHealed(true);
		}
		destinationSoldier->setTraining(false);

		int transferTime = _transformationRule->getTransferTime() > 0 ? _transformationRule->getTransferTime() : 24;
		Transfer *transfer = new Transfer(transferTime);
		transfer->setSoldier(destinationSoldier);
		_base->getTransfers().push_back(transfer);
	}

	destinationSoldier->transform(game.getMod(), _transformationRule, _sourceSoldier, _base);
}

void SoldierTransformationState::retire()
{
	// remove the soldier from existence
	{
		if (_sourceSoldier->getDeath())
		{
			// I wonder if anyone will ever use THIS option
			auto it = find(game.savedGame()->getDeadSoldiers().begin(), game.savedGame()->getDeadSoldiers().end(), _sourceSoldier);
			if (it != game.savedGame()->getDeadSoldiers().end())
			{
				delete (*it);
				game.savedGame()->getDeadSoldiers().erase(it);
			}
		}
		else
		{
			auto it = find(_base->soldiers().begin(), _base->soldiers().end(), _sourceSoldier);
			if (it != _base->soldiers().end())
			{
				delete (*it);
				_base->soldiers().erase(it);
			}
		}
	}

	// create the item
	{
		int transferTime = _transformationRule->getTransferTime() > 0 ? _transformationRule->getTransferTime() : 1;
		Transfer *transfer = new Transfer(transferTime);
		transfer->setItems(game.getMod()->getItem(_transformationRule->getProducedItem(), true), 1);
		_base->getTransfers().push_back(transfer);
	}
}

/**
 * Handles pressing the Left arrow button
 * @param action A pointer to an Action.
 */
void SoldierTransformationState::btnLeftArrowClick(Action *action)
{
	auto iter = find(_filteredListOfSoldiers->begin(), _filteredListOfSoldiers->end(), _sourceSoldier);
	if (iter == _filteredListOfSoldiers->begin())
	{
		iter = _filteredListOfSoldiers->end();
	}

	--iter;
	_sourceSoldier = *iter;
	initTransformationData();
}

/**
 * Handles pressing the Right arrow button
 * @param action A pointer to an Action.
 */
void SoldierTransformationState::btnRightArrowClick(Action *action)
{
	auto iter = find(_filteredListOfSoldiers->begin(), _filteredListOfSoldiers->end(), _sourceSoldier);
	if (iter == _filteredListOfSoldiers->end() - 1)
	{
		iter = _filteredListOfSoldiers->begin();
	}
	else
	{
		++iter;
	}

	_sourceSoldier = *iter;
	initTransformationData();
}

}
