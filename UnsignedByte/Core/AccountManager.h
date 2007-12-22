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
#include <vector>

#include "singleton.h"
#include "db.h"

namespace mud 
{ 
	class Account; 
	typedef SmartPtr<Account> AccountPtr;
}

typedef const std::string& cstring;
typedef std::map<value_type,mud::AccountPtr> accounts_m;
typedef std::map<std::string,mud::AccountPtr> accounts_ms;
typedef std::map<std::string, value_type> reverseStringKey;

namespace mud
{
	class AccountManager : public Singleton<mud::AccountManager>
	{
	public:
		std::vector<std::string> List();
		void Close(AccountPtr account);
		bool IllegalName(const std::string& name);
		
		value_type Add();
		mud::AccountPtr GetByKey(value_type id);
		mud::AccountPtr GetByName(cstring name);
		
		value_type lookupByName(cstring value);
		
		void Close(value_type accountid);
		
	private:
		AccountPtr cacheAccount(db::Accounts* d);
		
		accounts_m m_byKey;
		accounts_ms m_byName;
		reverseStringKey m_lookupByName;

	private:
		AccountManager(void) {};
		AccountManager(const AccountManager& rhs);
		AccountManager operator=(const AccountManager& rhs);
		~AccountManager(void) {};
		
		friend class Singleton<mud::AccountManager>;
	};
}