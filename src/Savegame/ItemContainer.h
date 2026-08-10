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
#include <QtQml>
#include "../Engine/Yaml.h"

namespace OpenXcom
{

class Mod;
class RuleItem;

	class ItemCounter
	{
		Q_GADGET
		QML_ELEMENT

		Q_PROPERTY(RuleItem* item READ item FINAL)
		Q_PROPERTY(int count READ count FINAL)
		const RuleItem* m_Item = nullptr;
		int m_Count = 0;
	  public:
		ItemCounter() = default;
		ItemCounter(const RuleItem* item, int count);

		RuleItem* item();
		const RuleItem* item() const;
		int count() const;
		void setCount(int newCount);
	};

	/**
	 * Represents the items contained by a certain entity,
	 * like base stores, craft equipment, etc.
	 * Handles all necessary item management tasks.
	 */
	class ItemContainer: public QObject
	{
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(std::vector<ItemCounter> content READ content CONSTANT FINAL)
		std::vector<ItemCounter> m_Content;
	public:
		/// Clone container.
		void clone(const ItemContainer& other);
		/// Loads the item container from YAML.
		void load(const YAML::YamlNodeReader& reader, const Mod* mod);
		/// Saves the item container to YAML.
		void save(YAML::YamlNodeWriter writer) const;
		/// Adds an item to the container.
		void addItem(const RuleItem* item, int qty = 1);
		/// Removes an item from the container.
		void removeItem(const std::string &id, int qty = 1);
		/// Removes an item from the container.
		void removeItem(const RuleItem* item, int qty = 1);
		/// Gets an item in the container.
		int countOf(const std::string &id) const;
		/// Gets an item in the container.
		Q_INVOKABLE int countOf(const RuleItem* item) const;
		/// Gets the total quantity of items in the container.
		int totalCount() const;
		/// Gets the total size of items in the container.
		double totalSize() const;
		/// Check if have any item
		bool empty() const { return m_Content.empty(); }
		/// Clear all content.
		void clear() { m_Content.clear(); }
		/// Gets all the items in the container.
		const std::vector<ItemCounter>& content() const;
	  private:
		std::vector<ItemCounter>::iterator find(const RuleItem* item);
		std::vector<ItemCounter>::iterator find(const std::string &id);
	};

}

Q_DECLARE_METATYPE(OpenXcom::ItemCounter)
Q_DECLARE_METATYPE(std::vector<OpenXcom::ItemCounter>)