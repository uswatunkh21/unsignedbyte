/***************************************************************************
 *   Copyright (C) 2008 by Sverre Rabbelier                                *
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

#include "SavableHeaders.h"

namespace mud
{
	class ExitManager;
	
	class Exit : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		value_type getRoom() const;
		const std::string& getDir() const;

		/**
		 * \brief Setters
		 */
		void setRoom(value_type room);
		void setDir(const std::string& dir);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TableImplPtr getTable() const;
		
		/**
		 * \brief Database operations
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		friend class mud::ExitManager; // For constructor
		friend SmartPtrDelete(mud::Exit);
		
		SavableManagerPtr m_exit;

		/**
		 * \brief Constructor
		 * \param exit The DB object
		 */
		Exit(SavableManagerPtr exit);
		
		Exit(const Exit& rhs);
		Exit operator=(const Exit& rhs);
			
		/**
		 * \brief Default destructor
		 */
		~Exit(void);
	};
}
