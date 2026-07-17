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

#include <sstream>
#include "../fmath.h"
#include "ArticleStateArmor.h"
#include "../Mod/ArticleDefinition.h"
#include "../Mod/Mod.h"
#include "../Mod/Armor.h"
#include "../Engine/Game.h"
#include "../Engine/Surface.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/FileMap.h"
#include "../Engine/Unicode.h"
#include "../Interface/Text.h"
#include "../Interface/TextButton.h"
#include "../Interface/TextList.h"
#include "../Mod/RuleInterface.h"
#include "../Savegame/Soldier.h"

namespace OpenXcom
{

	ArticleStateArmor::ArticleStateArmor(ArticleDefinitionArmor *defs, std::shared_ptr<ArticleCommonState> state) : ArticleState(defs->id, std::move(state)), _row(0)
	{
		Armor *armor = game.getMod()->getArmor(defs->id, true);

		// add screen elements
		_txtTitle = new Text(300, 17, 5, 24);

		// Set palette
		Surface* customArmorSprite = defs->image_id.empty() ? nullptr : game.getMod()->getSurface(defs->image_id, true);
		if (defs->customPalette && customArmorSprite)
		{
			setCustomPalette(customArmorSprite->getPalette(), Mod::BATTLESCAPE_CURSOR);
		}
		else
		{
			setStandardPalette("PAL_BATTLEPEDIA");
		}

		RuleInterface* itf = game.getMod()->getInterface("articleArmor");
		_buttonColor = itf->getElement("button")->color;
		_textColor = itf->getElement("text")->color;
		_textColor2 = itf->getElement("text")->color2;
		_listColor1 = itf->getElement("list")->color;
		_listColor2 = itf->getElement("list")->color2;

		ArticleState::initLayout();

		// add other elements
		add(_txtTitle);

		// Set up objects
		_btnOk->setColor(_buttonColor);
		_btnPrev->setColor(_buttonColor);
		_btnNext->setColor(_buttonColor);
		_btnInfo->setColor(_buttonColor);
		_btnInfo->setVisible(game.getMod()->getShowPediaInfoButton());

		_txtTitle->setColor(_textColor);
		_txtTitle->setBig();
		_txtTitle->setText(ltr(defs->getTitleForPage(_state->current_page)));

		// optional background image
		if (!defs->customPalette)
		{
			auto& bgImageName = itf->getBackgroundImage(game.getMod(), game.savedGame());
			if (!bgImageName.empty())
			{
				game.getMod()->getSurface(bgImageName)->blitNShade(_bg, 0, 0);
			}
		}

		if (customArmorSprite)
		{
			// blit on the background, so that text and button are always visible
			customArmorSprite->blitNShade(_bg, 0, 0);
		}
		else if (armor->hasLayersDefinition())
		{
			// dummy default soldier (M0)
			Soldier *s = new Soldier(game.getMod()->getSoldier(game.getMod()->getSoldiersList().front(), true), armor, 0 /*nationality*/, 0 /*id*/);
			s->setGender(GENDER_MALE);
			s->setLook(LOOK_BLONDE);
			s->setLookVariant(0);

			for (const auto& layer : s->getArmorLayers())
			{
				auto* surf = game.getMod()->getSurface(layer, true);
				surf->blitNShade(_bg, 0, 0);
			}
			delete s;
			s = nullptr;
		}
		else
		{
			std::string look = armor->getSpriteInventory();
			look += "M0.SPK";
			if (!game.getMod()->getSurface(look, false))
			{
				look = armor->getSpriteInventory() + ".SPK";
			}
			if (!game.getMod()->getSurface(look, false))
			{
				look = armor->getSpriteInventory();
			}
			game.getMod()->getSurface(look, true)->blitNShade(_bg, 0, 0);
		}


		_lstInfo = new TextList(150, 96, 150, 46);
		add(_lstInfo);

		_lstInfo->setColor(_listColor1);
		_lstInfo->setColumns(2, 125, 25);
		_lstInfo->setDot(true);

		_txtInfo = new Text(300, 48, 8, 150);
		add(_txtInfo);

		_txtInfo->setColor(_textColor);
		_txtInfo->setSecondaryColor(_textColor2);
		_txtInfo->setWordWrap(true);
		_txtInfo->setScrollable(true);
		_txtInfo->setText(ltr(defs->getTextForPage(_state->current_page)));

		// Add armor values
		addStat("STR_FRONT_ARMOR", armor->getFrontArmor());
		addStat("STR_LEFT_ARMOR", armor->getLeftSideArmor());
		addStat("STR_RIGHT_ARMOR", armor->getRightSideArmor());
		addStat("STR_REAR_ARMOR", armor->getRearArmor());
		addStat("STR_UNDER_ARMOR", armor->getUnderArmor());

		_lstInfo->addRow(0);
		++_row;

		if (options1.oxcePediaSortResistances() == 0)
		{
			// Add damage modifiers
			for (int i = 0; i < DAMAGE_TYPES; ++i)
			{
				ItemDamageType dt = (ItemDamageType)i;
				int percentage = (int)Round(armor->getDamageModifier(dt) * 100.0f);
				std::string damage = getDamageTypeText(dt);
				if (percentage != 100 && damage != "STR_UNKNOWN")
				{
					addModifier(damage, Unicode::formatPercentage(percentage));
				}
			}
		}
		else
		{
			// Add resistances
			int counter = 0;
			bool first = true;
			for (int i = 0; i < DAMAGE_TYPES; ++i)
			{
				ItemDamageType dt = (ItemDamageType)i;
				int percentage = (int)Round(armor->getDamageModifier(dt) * 100.0f);
				std::string damage = getDamageTypeText(dt);
				if (percentage < 100 && damage != "STR_UNKNOWN")
				{
					addModifier(damage, Unicode::formatPercentage(percentage));
					counter++;
				}
			}
			if (options1.oxcePediaSortResistances() >= 2)
			{
				// Add standard damage (100%)
				for (int i = 0; i < DAMAGE_TYPES; ++i)
				{
					ItemDamageType dt = (ItemDamageType)i;
					int percentage = (int)Round(armor->getDamageModifier(dt) * 100.0f);
					std::string damage = getDamageTypeText(dt);
					if (percentage == 100 && damage != "STR_UNKNOWN")
					{
						if (counter > 0 && first)
						{
							first = false;
							counter = 0;
							_lstInfo->addRow(0);
							++_row;
						}
						addModifier(damage, Unicode::formatPercentage(percentage));
						counter++;
					}
				}
			}
			// Add vulnerabilities
			first = true;
			for (int i = 0; i < DAMAGE_TYPES; ++i)
			{
				ItemDamageType dt = (ItemDamageType)i;
				int percentage = (int)Round(armor->getDamageModifier(dt) * 100.0f);
				std::string damage = getDamageTypeText(dt);
				if (percentage > 100 && damage != "STR_UNKNOWN")
				{
					if (counter > 0 && first)
					{
						first = false;
						counter = 0;
						_lstInfo->addRow(0);
						++_row;
					}
					addModifier(damage, Unicode::formatPercentage(percentage));
				}
			}
		}

		_lstInfo->addRow(0);
		++_row;

		// Add unit stats
		addStat("STR_TIME_UNITS", armor->getStats()->tu, true);
		addStat("STR_STAMINA", armor->getStats()->stamina, true);
		addStat("STR_HEALTH", armor->getStats()->health, true);
		addStat("STR_BRAVERY", armor->getStats()->bravery, true);
		addStat("STR_REACTIONS", armor->getStats()->reactions, true);
		addStat("STR_FIRING_ACCURACY", armor->getStats()->firing, true);
		addStat("STR_THROWING_ACCURACY", armor->getStats()->throwing, true);
		addStat("STR_MELEE_ACCURACY", armor->getStats()->melee, true);
		addStat("STR_STRENGTH", armor->getStats()->strength, true);
		addStat("STR_MANA_POOL", armor->getStats()->mana, true);
		addStat("STR_PSIONIC_STRENGTH", armor->getStats()->psiStrength, true);
		addStat("STR_PSIONIC_SKILL", armor->getStats()->psiSkill, true);

		centerAllSurfaces();
	}

	ArticleStateArmor::~ArticleStateArmor()
	{}

	void ArticleStateArmor::addStat(const std::string &label, int stat, bool plus)
	{
		if (stat != 0)
		{
			std::ostringstream ss;
			if (plus && stat > 0)
				ss << "+";
			ss << stat;
			_lstInfo->addRow(2, ltr(label).c_str(), ss.str().c_str());
			_lstInfo->setCellColor(_row, 1, _listColor2);
			++_row;
		}
	}

	void ArticleStateArmor::addModifier(const std::string &label, const std::string &stat)
	{
		std::string translation = ltr(label);
		if (translation.length() > 2) // filter out unused OXCE damage types
		{
			_lstInfo->addRow(2, ltr(label).c_str(), stat.c_str());
			_lstInfo->setCellColor(_row, 1, _listColor2);
			++_row;
		}
	}
}
