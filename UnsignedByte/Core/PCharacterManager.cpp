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

#include <sstream>

#include "PCharacterManager.h"
#include "PCharacter.h"
#include "Exceptions.h"
#include "TableImpls.h"
#include "db.h"

using mud::PCharacterManager;
using mud::PCharacter;
using mud::PCharacterPtr;

bool PCharacterManager::isActive(value_type id)
{
	return m_activeCharactersByKey.find(id) != m_activeCharactersByKey.end();
}

bool PCharacterManager::isActive(cstring value)
{
	return m_activeCharactersByName.find(value) != m_activeCharactersByName.end();
}

mud::PCharacterPtr PCharacterManager::GetByKey(value_type id)
{
	PCharacterPtr p = m_activeCharactersByKey[id];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "PCharacterManager::GetPCharacterByKey(), The id '" << id << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());
}

mud::PCharacterPtr PCharacterManager::GetByName(cstring value)
{
	PCharacterPtr p = m_activeCharactersByName[value];
	if(p)
		return p;
		
	std::ostringstream err;
	err << "PCharacterManager::GetPCharacterByKey(), No character with name '" << value << "' has not been loaded yet.";
	throw std::invalid_argument(err.str());	
}

mud::PCharacterPtr PCharacterManager::LoadByKey(UBSocket* sock, value_type id)
{
	if(m_activeCharactersByKey.find(id) != m_activeCharactersByKey.end())
	{
		std::ostringstream err;
		err << "PCharacterManager::LoadPCharacterByKey(), id '" << id << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}
	
	KeyPtr key(new Key(db::EntitiesFields::Get()->ENTITYID, id));
	SavableManagerPtr manager = SavableManager::bykeys(key);
	PCharacterPtr p(new PCharacter(sock, manager));
	m_activeCharactersByKey[id] = p;
	m_activeCharactersByName[p->getName()] = p;
	return p;
}

mud::PCharacterPtr PCharacterManager::LoadByName(UBSocket* sock, cstring name)
{
	if(m_activeCharactersByName.find(name) != m_activeCharactersByName.end())
	{
		std::ostringstream err;
		err << "PCharacterManager::LoadPCharacterByKey(), A character with name '" << name << "' has already been loaded.";
		throw std::invalid_argument(err.str());
	}	
	
	ValuePtr value(new Value(db::EntitiesFields::Get()->NAME, name));
	SavableManagerPtr manager = SavableManager::byvalue(value);
	PCharacterPtr p(new PCharacter(sock, manager));
	m_activeCharactersByName[name] = p;
	m_activeCharactersByKey[p->getID()] = p;
	return p;
}

void mud::PCharacterManager::UnloadByKey(value_type id)
{
	charactersByKey::iterator it_key = m_activeCharactersByKey.find(id);
	Assert(it_key != m_activeCharactersByKey.end());
	
	mud::PCharacterPtr character = it_key->second;
	std::string name = character->getName();
	
	charactersByName::iterator it_name = m_activeCharactersByName.find(name);
	Assert(it_name != m_activeCharactersByName.end());
	
	m_activeCharactersByKey.erase(it_key);
	m_activeCharactersByName.erase(it_name);
}
