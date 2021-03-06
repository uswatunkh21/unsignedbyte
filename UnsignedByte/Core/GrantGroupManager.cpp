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

#include "GrantGroupManager.h"
#include "GrantGroup.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::GrantGroupManager;
using mud::GrantGroup;
using mud::GrantGroupPtr;

std::vector<std::string> GrantGroupManager::List()
{
	return GetTable()->tableList();
}

TableImplPtr GrantGroupManager::GetTable()
{
	return db::TableImpls::Get()->GRANTGROUPS;
}

KeysPtr GrantGroupManager::Add()
{
	SavableManagerPtr manager = SavableManager::getnew(db::TableImpls::Get()->GRANTGROUPS);
	manager->save();
	return manager->getkeys();
}

mud::GrantGroupPtr GrantGroupManager::GetByKey(value_type id)
{
	KeysPtr keys(new Keys(db::TableImpls::Get()->GRANTGROUPS));
	KeyPtr key(new Key(db::GrantGroupsFields::Get()->GRANTGROUPID, id));
	keys->addKey(key);
	
	SavableManagerPtr manager = SavableManager::bykeys(keys);
	GrantGroupPtr p(new GrantGroup(manager));
	return p;
}

mud::GrantGroupPtr GrantGroupManager::GetByName(cstring value)
{
	ValuePtr val(new Value(db::GrantGroupsFields::Get()->NAME, value));
	SavableManagerPtr manager = SavableManager::byvalue(val);
	GrantGroupPtr p(new GrantGroup(manager));
	return p;
}

value_type GrantGroupManager::lookupByName(cstring value)
{
	ValuePtr val(new Value(db::GrantGroupsFields::Get()->NAME, value));
	KeysPtr keys = SavableManager::lookupvalue(val);
	value_type id = keys->getKey(db::GrantGroupsFields::Get()->GRANTGROUPID)->getValue();
	return id;
}
