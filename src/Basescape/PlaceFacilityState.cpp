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
#include "PlaceFacilityState.h"
#include "../Engine/Game.h"
#include "../Engine/Sound.h"
#include "../Mod/Mod.h"
#include "../Engine/LocalizedText.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "BaseView.h"
#include "../Savegame/Base.h"
#include "../Savegame/BaseFacility.h"
#include "../Savegame/ItemContainer.h"
#include "../Mod/RuleBaseFacility.h"
#include "../Savegame/SavedGame.h"
#include "../Engine/Unicode.h"
#include "../Mod/RuleInterface.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the Place Facility window.
 * @param game Pointer to the core game.
 * @param base Pointer to the base to get info from.
 * @param rule Pointer to the facility ruleset to build.
 */
PlaceFacilityState::PlaceFacilityState(Base *base, const RuleBaseFacility *rule, BaseFacility *origFac) : _base(base), _rule(rule), _origFac(origFac)
{
	_screen = false;

	// Create objects
	_window = new Window(this, 128, 160, 192, 40);
	_view = new BaseView(192, 192, 0, 8);
	_btnCancel = new TextButton(112, 16, 200, 176);
	_txtFacility = new Text(110, 9, 202, 50);
	_txtCost = new Text(110, 9, 202, 62);
	_numCost = new Text(110, 17, 202, 70);
	_numResources = new Text(110, 25, 202, 87);
	const size_t resourceTextOffset = 9*std::min((size_t)3, (_origFac == nullptr ? _rule->getBuildCostItems().size() : 0));
	_txtTime = new Text(110, 9, 202, 90+resourceTextOffset);
	_numTime = new Text(110, 17, 202, 98+resourceTextOffset);
	_txtMaintenance = new Text(110, 9, 202, 118+resourceTextOffset);
	_numMaintenance = new Text(110, 17, 202, 126+resourceTextOffset);

	// Set palette
	setInterface("placeFacility");

	add(_window, "window", "placeFacility");
	add(_view, "baseView", "basescape");
	add(_btnCancel, "button", "placeFacility");
	add(_txtFacility, "text", "placeFacility");
	add(_txtCost, "text", "placeFacility");
	add(_numCost, "numbers", "placeFacility");
	add(_numResources, "numbers", "placeFacility");
	add(_txtTime, "text", "placeFacility");
	add(_numTime, "numbers", "placeFacility");
	add(_txtMaintenance, "text", "placeFacility");
	add(_numMaintenance, "numbers", "placeFacility");

	centerAllSurfaces();

	// Set up objects
	setWindowBackground(_window, "placeFacility");

	auto* itf = game.getMod()->getInterface("basescape")->getElementOptional("trafficLights");
	if (itf)
	{
		_view->setOtherColors(itf->color, itf->color2, itf->border, !itf->TFTDMode);
	}
	_view->setTexture(game.getMod()->getSurfaceSet("BASEBITS.PCK"));
	_view->setBase(_base);
	_view->setSelectable(rule->getSizeX(), rule->getSizeY());
	_view->onMouseClick((ActionHandler)&PlaceFacilityState::viewClick);

	_btnCancel->setText(ltr("STR_CANCEL"));
	_btnCancel->onMouseClick((ActionHandler)&PlaceFacilityState::btnCancelClick);
	_btnCancel->onKeyboardPress((ActionHandler)&PlaceFacilityState::btnCancelClick, options1.keyCancel());

	_txtFacility->setText(ltr(_rule->getType()));

	_txtCost->setText(ltr("STR_COST_UC"));

	_numCost->setBig();
	_numCost->setText(Unicode::formatFunding(_origFac != nullptr ? 0 : _rule->getBuildCost()));

	if (_origFac == nullptr && !_rule->getBuildCostItems().empty())
	{
		std::ostringstream ss;

		// Currently, the text box will only fit three lines of items.
		// But I'm going to add everything to the list anyway.
		for (auto& item : _rule->getBuildCostItems())
		{
			// Note: `item` is of the form (item name, (cost number, refund number))
			size_t max = 19;
			if (item.second.first > 9) --max;
			if (item.second.first > 99) --max;
			std::string name = ltr(item.first);
			if (Unicode::codePointLengthUTF8(name) > max)
			{
				name = Unicode::codePointSubstrUTF8(name, 0, max);
			}

			ss << name << ": " << item.second.first << std::endl;
		}
		_numResources->setText(ss.str());
	}

	_txtTime->setText(ltr("STR_CONSTRUCTION_TIME_UC"));

	_numTime->setBig();
	_numTime->setText(ltr("STR_DAY", _origFac != 0 ? 0 : _rule->getBuildTime()));

	_txtMaintenance->setText(ltr("STR_MAINTENANCE_UC"));

	_numMaintenance->setBig();
	_numMaintenance->setText(Unicode::formatFunding(_rule->getMonthlyCost()));
}

/**
 *
 */
PlaceFacilityState::~PlaceFacilityState()
{

}

/**
 * Returns to the previous screen.
 * @param action Pointer to an action.
 */
void PlaceFacilityState::btnCancelClick(Action *)
{
	game.popState();
}

/**
 * Processes clicking on facilities.
 * @param action Pointer to an action.
 */
void PlaceFacilityState::viewClick(Action *)
{
	if (_origFac != 0)
	{
		// EXPERIMENTAL!: just moving an existing facility
		if (_view->getGridX() == _origFac->getX() && _view->getGridY() == _origFac->getY())
		{
			// unchanged location -> no message, no cost.
			game.popState();
		}
		else if (_view->getPlacementError(_rule, _origFac))
		{
			game.errorMessage(QString::fromStdString(ltr("STR_CANNOT_BUILD_HERE")));
		}
		else
		{
			_origFac->setX(_view->getGridX());
			_origFac->setY(_view->getGridY());
			if (options1.allowBuildingQueue())
			{
				// first reset (maybe the moved facility is not queued anymore)
				if (abs(_origFac->getBuildTime()) > _rule->getBuildTime()) _origFac->setBuildTime(_rule->getBuildTime());
				// if it is still in the queue though, recalc
				if (_origFac->getBuildTime() > 0 && _view->isQueuedBuilding(_rule)) _origFac->setBuildTime(INT_MAX);
				_view->reCalcQueuedBuildings();
			}
			game.popState();
		}
	}
	else
	{
		// Pre-calculate refunds
		const BaseAreaSubset areaToBuildOverTemp = BaseAreaSubset(_rule->getSizeX(), _rule->getSizeY()).offset(_view->getGridX(), _view->getGridY());
		int refundValueTemp = 0;
		std::map<const std::string, int> refundItemsTemp;
		for (int i = _base->getFacilities().size() - 1; i >= 0; --i)
		{
			BaseFacility* checkFacilityTemp = _base->getFacilities().at(i);
			if (BaseAreaSubset::intersection(areaToBuildOverTemp, checkFacilityTemp->getPlacement()))
			{
				const std::map<std::string, std::pair<int, int> >& itemCostTemp = checkFacilityTemp->getRules()->getBuildCostItems();
				if (checkFacilityTemp->getBuildTime() > checkFacilityTemp->getRules()->getBuildTime())
				{
					refundValueTemp = checkFacilityTemp->getRules()->getBuildCost();
					for (auto& itemTemp : itemCostTemp)
						refundItemsTemp[itemTemp.first] += itemTemp.second.first;
				}
				else
				{
					refundValueTemp = checkFacilityTemp->getRules()->getRefundValue();
					for (auto& itemTemp : itemCostTemp)
						refundItemsTemp[itemTemp.first] += itemTemp.second.second;
				}
				if (checkFacilityTemp->getAmmo() > 0)
					refundItemsTemp[checkFacilityTemp->getRules()->getAmmoItem()->getType()] += checkFacilityTemp->getAmmo();
			}
		}

		// placing a brand new facility
		BasePlacementErrors placementErrorCode = _view->getPlacementError(_rule);
		if (placementErrorCode)
		{
			std::string errorKey;
			switch (placementErrorCode)
			{
				case BPE_Used_Stores:
					errorKey = "STR_FACILITY_IN_USE_STORAGE";
					break;
				case BPE_Used_Quarters:
					errorKey = "STR_FACILITY_IN_USE_QUARTERS";
					break;
				case BPE_Used_Laboratories:
					errorKey = "STR_FACILITY_IN_USE_LABORATORIES";
					break;
				case BPE_Used_Workshops:
					errorKey = "STR_FACILITY_IN_USE_WORKSHOPS";
					break;
				case BPE_Used_Hangars:
					errorKey = "STR_FACILITY_IN_USE_HANGARS";
					break;
				case BPE_Used_PsiLabs:
					errorKey = "STR_FACILITY_IN_USE_PSI_LABS";
					break;
				case BPE_Used_Gyms:
					errorKey = "STR_FACILITY_IN_USE_GYMS";
					break;
				case BPE_Used_AlienContainment:
					errorKey = "STR_FACILITY_IN_USE_PRISONS";
					break;
				case BPE_NotConnected:
					errorKey = "STR_CANNOT_BUILD_HERE";
					break;
				case BPE_Used:
					errorKey = "STR_FACILITY_IN_USE";
					break;
				case BPE_Upgrading:
					errorKey = "STR_CANNOT_UPGRADE_FACILITY_ALREADY_UPGRADING";
					break;
				case BPE_UpgradeSizeMismatch:
					errorKey = "STR_CANNOT_UPGRADE_FACILITY_WRONG_SIZE";
					break;
				case BPE_UpgradeRequireSpecific:
					errorKey = "STR_CANNOT_UPGRADE_FACILITY_WRONG_TYPE";
					break;
				case BPE_UpgradeDisallowed:
					errorKey = "STR_CANNOT_UPGRADE_FACILITY_DISALLOWED";
					break;
				case BPE_Queue:
					errorKey = "STR_CANNOT_BUILD_QUEUE_OFF";
					break;
				case BPE_ForbiddenByOther:
					errorKey = "STR_FACILITY_FORBIDDEN_BY_OTHER";
					break;
				case BPE_ForbiddenByThis:
					errorKey = "STR_FACILITY_OTHER_FORBIDDEN_BY_THIS";
					break;
				case BPE_UpgradeOnly:
					errorKey = "STR_CANNOT_BUILD_UPGRADE_ONLY";
					break;
				default:
					errorKey = "STR_CANNOT_BUILD_HERE";
					break;
			}

			game.errorMessage(QString::fromStdString(ltr(errorKey)));
		}
		else if (game.savedGame()->getFunds() < (_rule->getBuildCost() - refundValueTemp))
		{
			game.popState();
			game.errorMessage(QString::fromStdString(ltr("STR_NOT_ENOUGH_MONEY")));
		}
		else
		{
			for (const auto& item: _rule->getBuildCostItems())
			{
				int needed = (item.second.first - refundItemsTemp[item.first]) - _base->getStorageItems().getItem(item.first);
				if (needed > 0)
				{
					game.popState();
					game.errorMessage(QString::fromStdString(ltr("STR_NOT_ENOUGH_ITEMS").arg(ltr(item.first)).arg(needed)));
					return;
				}
			}
			// Remove any facilities we're building over
			double reducedBuildTime = 0.0;
			bool buildingOver = false;
			const BaseAreaSubset areaToBuildOver = BaseAreaSubset(_rule->getSizeX(), _rule->getSizeY()).offset(_view->getGridX(), _view->getGridY());
			for (int i = _base->getFacilities().size() - 1; i >= 0; --i)
			{
				BaseFacility *checkFacility = _base->getFacilities().at(i);
				if (BaseAreaSubset::intersection(areaToBuildOver, checkFacility->getPlacement()))
				{
					// Get a refund from the facility we're building over
					const std::map<std::string, std::pair<int, int> > &itemCost = checkFacility->getRules()->getBuildCostItems();

					if (checkFacility->getBuildTime() > checkFacility->getRules()->getBuildTime())
					{
						// Give full refund if this is a (not yet started) queued build.
						game.savedGame()->setFunds(game.savedGame()->getFunds() + checkFacility->getRules()->getBuildCost());
						for (auto& item : itemCost)
						{
							_base->getStorageItems().addItem(game.getMod()->getItem(item.first, true), item.second.first);
						}
					}
					else
					{
						// Give partial refund if this is a started build or a completed facility.
						game.savedGame()->setFunds(game.savedGame()->getFunds() + checkFacility->getRules()->getRefundValue());
						for (auto& item : itemCost)
						{
							_base->getStorageItems().addItem(game.getMod()->getItem(item.first, true), item.second.second);
						}

						// Reduce the build time of the new facility
						double oldSizeSquared = (checkFacility->getRules()->getSizeX() * checkFacility->getRules()->getSizeY());
						double newSizeSquared = (_rule->getSizeX() * _rule->getSizeY());
						reducedBuildTime += (checkFacility->getRules()->getBuildTime() - checkFacility->getBuildTime()) * oldSizeSquared / newSizeSquared;

						// This only counts as building over something if it wasn't in construction
						if (checkFacility->getBuildTime() == 0)
							buildingOver = true;
					}
					if (checkFacility->getAmmo() > 0)
					{
						// Full refund of loaded ammo
						_base->getStorageItems().addItem(checkFacility->getRules()->getAmmoItem(), checkFacility->getAmmo());
						checkFacility->setAmmo(0);
					}

					// Remove the facility from the base
					_base->getFacilities().erase(_base->getFacilities().begin() + i);
					delete checkFacility;
				}

			}

			BaseFacility *fac = new BaseFacility(_rule, _base);
			fac->setX(_view->getGridX());
			fac->setY(_view->getGridY());
			fac->setBuildTime(_rule->getBuildTime());
			if (buildingOver)
			{
				fac->setIfHadPreviousFacility(true);
				reducedBuildTime = reducedBuildTime * game.getMod()->getBuildTimeReductionScaling() / 100.0;
				int reducedBuildTimeRounded = (int)std::round(reducedBuildTime);
				fac->setBuildTime(std::max(1, fac->getBuildTime() - reducedBuildTimeRounded));
			}
			_base->getFacilities().push_back(fac);
			if (fac->getRules()->getPlaceSound() != Mod::NO_SOUND)
			{
				game.getMod()->getSound("GEO.CAT", fac->getRules()->getPlaceSound())->play();
			}
			if (options1.allowBuildingQueue())
			{
				if (_view->isQueuedBuilding(_rule)) fac->setBuildTime(INT_MAX);
				_view->reCalcQueuedBuildings();
			}
			_view->setBase(_base);
			game.savedGame()->setFunds(game.savedGame()->getFunds() - _rule->getBuildCost());
			for (const auto& item: _rule->getBuildCostItems())
			{
				_base->getStorageItems().removeItem(item.first, item.second.first);
			}
			if (!game.isShiftPressed())
			{
				game.popState();
			}
		}
	}
}

}
