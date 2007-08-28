/***************************************************************************
 *   Copyright (C) 2007 by Sverre Rabbelier                                *
 *   sverre@rabbelier.nl                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#pragma once

#include <string>
#include "Savable.h"
#include "ub.h"

namespace db { class Areas; };
class Room;

class Area : public Savable
{
public:
	/**
	 * \brief Getters
	 */
	std::string& getName() const { return m_area->name; };
	std::string& getDescription() const { return m_area->description; };
	long getHeight() const { return m_area->height; };
	long getWidth() const { return m_area->width; };

	/**
	 * \brief Setters
	 */
	void setName(const std::string& name) { m_area->name = name; };
	void setDescription(const std::string& description) { m_area->description = description; };
	void setHeight(long height) { m_area->height = height; };
	void setWidth(long width) { m_area->width = width; };

	/**
	 * \brief Utilities
	 */
	std::vector<std::string> Show();
	std::string ShowShort();
	Table* getTable() const;
	
	/**
	 * \brief Static utilities
	 */
	static std::vector<std::string> List();
	static void Close(Area* area);
	
	/**
	 * \brief Database operations
	 */
	void Delete();
	void Save();
	bool Exists();

private:
	friend class Cache; // For constructor
	db::Areas* m_area;

	/**
	 * \brief Constructor
	 * \param area The DB object
	 * \return 
	 */
	Area(db::Areas* area);
	
	Area(const Area& rhs);
	Area operator=(const Area& rhs) { return *this; };
		
	/**
	 * \brief Default destructor
	 */
	~Area(void);
};