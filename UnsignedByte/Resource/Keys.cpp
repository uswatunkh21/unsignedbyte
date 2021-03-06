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

#include "Keys.h"
#include "Key.h"
#include "KeyDef.h"
#include "TableImpl.h"
#include "FieldImpl.h"
#include "Parse.h"
#include "StringUtilities.h"

Keys::Keys(TableImplPtr table) : 
m_table(table) 
{ 
	Assert(table); 
}

Keys::Keys(TableImplPtr table, cstring initstring) :
m_table(table)
{
	Assert(table);
	Parse p(initstring);
		
	try
	{
		for(KeyDefs::const_iterator it = m_table->keyimplbegin(); it != m_table->keyimplend(); it++)
		{
			Assert(*it);
			
			std::string keystring = p.getword();
			int value = atoi(keystring.c_str());
			KeyPtr key(new Key(*it, value));
			addKey(key);
		}
	}
	catch(std::exception& e) 
	{
		throw std::invalid_argument("Keys::Keys(), could not parse initstring.");
	}
}

Keys::~Keys() 
{ 
	
}

KeyPtr Keys::getKey(KeyDefPtr key) const
{
	Assert(key);
	KeyMap::const_iterator it = m_keys.find(key.get());
	Assert(it != m_keys.end());
		
	return it->second;
}

TableImplPtr Keys::getTable() const 
{ 
	return m_table; 
}

void Keys::addKey(KeyPtr key)
{
	Assert(key);
	Assert(key->getTable() == m_table);
		
	m_keys[key->getKeyDef().get()] = key;
}
	
std::string Keys::toString() const
{
	std::string result;
	
	return result;
}

size_t Keys::size() const 
{ 
	return m_keys.size(); 
}

KeyPtr Keys::first() const 
{ 
	return m_keys.begin()->second; 
}

KeyMap::const_iterator Keys::begin() const 
{ 
	return m_keys.begin(); 
}

KeyMap::const_iterator Keys::end() const 
{ 
	return m_keys.end(); 
}

KeyMap::const_iterator Keys::find(KeyDefPtr key) const 
{ 
	Assert(key); 
	
	return m_keys.find(key.get()); 
}

void Keys::setDirty(KeysPtr oldKeys)
{
	for(KeyMap::iterator it = m_keys.begin(); it != m_keys.end(); it++)
	{
		KeyPtr key = it->second;
		KeyMap::const_iterator other = oldKeys->find(key->getKeyDef());
		KeyPtr otherKey = other->second;
		if(key->getValue() != otherKey->getValue())
			key->setDirty(true);
	}
}

Strings Keys::getDiff(KeysPtr orig) const
{
	Strings result;
	
	for(KeyMap::const_iterator it = m_keys.begin(); it != m_keys.end(); it++)
	{
		KeyPtr key = it->second;
		Assert(key);
		if(!key->isDirty())
			continue;
			
		KeyDefPtr keydef = key->getKeyDef();
		Assert(keydef);
		
		KeyPtr origKey = orig->getKey(keydef);
		Assert(origKey);
			
		std::string line = "Changed key '";
		line.append(keydef->getName());
		line.append("' from '");
		line.append(String::Get()->fromInt(origKey->getValue()));
		line.append("' to '");
		line.append(String::Get()->fromInt(key->getValue()));
		line.append("'.");
		
		result.push_back(line);
	}
	
	return result;
}
