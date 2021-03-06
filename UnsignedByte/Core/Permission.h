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
	class Permission : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */ 
		long getAccount() const;
		long getGrantGroup() const;
		
		bool hasGrant() const;
		bool hasLog() const;
		
		void setGrant(bool grant);
		void setLog(bool log);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TableImplPtr getTable() const;
		
		/**
		 * \brief Database utilities
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		SavableManagerPtr m_permission;

		Permission(SavableManagerPtr Permission);
		Permission(const Permission& rhs);
		Permission operator=(const Permission& rhs);
		~Permission(void);
		
		friend class PermissionManager;
		friend SmartPtrDelete(mud::Permission);
		
		enum GRANTS
		{
			GRANT_NOTSET, // grant for this grantgroup is not set
			GRANT_ENABLE, // explicitly enable the grantgroup
			GRANT_DISABLE, // explicitly disable the grantgroup
			GRANT_ENABLEANDLOG, // enable and log the command
			GRANT_DISABLEANDLOG, // enable and log the attemp
		};
	};
}
