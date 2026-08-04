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
#include "ItemContainer.h"
#include "../Mod/Mod.h"
#include "../Mod/RuleItem.h"

namespace str = std::ranges;

namespace OpenXcom
{
	ItemCounter::ItemCounter(const RuleItem *item, int count):
		m_Item(item),
		m_Count(count)
	{

	}

	const RuleItem *ItemCounter::item() const
	{
		return m_Item;
	}

	int ItemCounter::count() const
	{
		return m_Count;
	}

	void ItemCounter::setCount(int newCount)
	{
		m_Count = newCount;
	}

	/**
	 * Loads the item container from a YAML file.
	 * @param node YAML node.
	 */
	void ItemContainer::clone(const ItemContainer &other)
	{
		_qty = other.getContents();
	}

	void ItemContainer::load(const YAML::YamlNodeReader& reader, const Mod* mod)
	{
		if (!reader || !reader.isMap())
			return;
		_qty.clear();
		for (const auto& item : reader.children())
		{
			std::string name = item.readKey<std::string>();

			if (const auto* type = mod->getItem(name))
			{
				_qty.emplace_back(type, item.readVal<int>());
			}
			else
			{
				Log(LOG_ERROR) << "Failed to load item " << name;
			}
		}
	}

	/**
	 * Saves the item container to a YAML file.
	 * @return YAML node.
	 */
	void ItemContainer::save(YAML::YamlNodeWriter writer) const
	{
		writer.setAsMap();
		// item containers are sorted alphabetically in the yaml mapping
		std::vector<std::pair<std::string, int>> sortedItems;
		sortedItems.reserve(_qty.size());

		for (auto& pair : _qty)
			sortedItems.emplace_back(pair.item()->getType(), pair.count());

		str::sort(sortedItems, [](auto& a, auto& b){ return a < b; });
		for (auto& pair : sortedItems)
			writer.write(writer.saveString(pair.first), pair.second);
	}

	/**
	 * Adds an item amount to the container.
	 * @param id Item ID.
	 * @param qty Item quantity.
	 */
	void ItemContainer::addItem(const RuleItem* item, int qty)
	{
		if (item)
		{
			if(auto it = find(item);
					it == _qty.end())
			{
				_qty.emplace_back(item, qty);
			}
			else
			{
				it->setCount(qty);
			}
		}
	}

	/**
	 * Removes an item amount from the container.
	 * @param id Item ID.
	 * @param qty Item quantity.
	 */
	void ItemContainer::removeItem(const std::string &id, int qty)
	{
		if (Mod::isEmptyRuleName(id))
		{
			return;
		}

		if (auto it = find(id);
				 it != _qty.end())
		{
			if (qty < it->count())
			{
				it->setCount(it->count() - qty);
			}
			else
			{
				_qty.erase(it);
			}
		}
	}

	/**
	 * Removes an item amount from the container.
	 * @param id Item ID.
	 * @param qty Item quantity.
	 */
	void ItemContainer::removeItem(const RuleItem* item, int qty)
	{
		if (item)
		{
			if (auto it = find(item); it != _qty.end())
			{
				if (qty < it->count())
				{
					it->setCount(it->count() - qty);
				}
				else
				{
					_qty.erase(it);
				}
			}
		}
	}

	/**
	 * Returns the quantity of an item in the container.
	 * @param id Item ID.
	 * @return Item quantity.
	 */
	int ItemContainer::getItem(const std::string &id) const
	{
		if (Mod::isEmptyRuleName(id))
		{
			return 0;
		}

		auto it = str::find_if(_qty, [&id](auto& ic) { return ic.item()->getType() == id; });
		return (it != _qty.end())?it->count()
								 :0;
	}

	/**
	 * Returns the quantity of an item in the container.
	 * @param id Item ID.
	 * @return Item quantity.
	 */
	int ItemContainer::getItem(const RuleItem* item) const
	{
		auto it = str::find_if(_qty, [item](auto& ic) { return ic.item() == item; });
		return (it != _qty.end())?it->count()
								  :0;
	}

	/**
	 * Returns the total quantity of the items in the container.
	 * @return Total item quantity.
	 */
	int ItemContainer::getTotalQuantity() const
	{
		int total = 0;
		for (const auto& pair : _qty)
		{
			total += pair.count();
		}
		return total;
	}

	/**
	 * Returns the total size of the items in the container.
	 * @return Total item size.
	 */
	double ItemContainer::getTotalSize() const
	{
		double total = 0;
		for (const auto& pair : _qty)
		{
			total += pair.item()->getSize() * pair.count();
		}
		return total;
	}

	std::vector<ItemCounter>::iterator ItemContainer::find(const RuleItem *item)
	{
		return str::find_if(_qty, [item](auto& ic) { return ic.item() == item; });
	}

	std::vector<ItemCounter>::iterator ItemContainer::find(const std::string &id)
	{
		return str::find_if(_qty, [&id](auto& ic) { return ic.item()->getType() == id; });
	}

	/**
	 * Returns all the items currently contained within.
	 * @return List of contents.
	 */
	const std::vector<ItemCounter>& ItemContainer::getContents() const
	{
		return _qty;
	}

}
