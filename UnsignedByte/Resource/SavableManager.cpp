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

#include "SavableManager.h"
#include "SqliteMgr.h"

#include "TableImpl.h"
#include "Value.h"
#include "FieldImpl.h"

SavableManager::SavableManager(TableImplPtr table) :
m_table(table),
m_newentry(true),
m_dirty(false)
{
	
}

SavableManager::~SavableManager()
{

}

SavableManagerPtr SavableManager::getnew(TableImplPtr table)
{
	SavableManagerPtr result(new SavableManager(table));
	return result;
}

SavableManagerPtr SavableManager::bykeys(TableImplPtr table, value_type key)
{
	Keys keys;
	keys.push_back(key);
	return bykeys(table, keys);
}

SavableManagerPtr SavableManager::bykeys(TableImplPtr table, Keys keys)
{
	// assert(keys.size() == m_table->keySize());
	
	SavableManagerPtr result = getnew(table);
	result->setkeys(keys);
	SqliteMgr::Get()->doSelect(result);
	return result;
}

SavableManagerPtr SavableManager::byvalue(ValuePtr value)
{	
	SavableManagerPtr result = getnew(value->getField()->getTable());
	result->m_lookupvalue = value;
	SqliteMgr::Get()->doLookup(result, value->getField());
	return result;
}

Keys SavableManager::lookupvalue(ValuePtr value)
{
	SavableManagerPtr result = byvalue(value);
	Keys keys = result->getkeys();
	return keys;
}

void SavableManager::erase()
{
	if(!m_newentry)
		SqliteMgr::Get()->doErase(this);
}

void SavableManager::save()
{
	if(m_newentry)
	{
		SqliteMgr::Get()->doInsert(this);
		m_newentry = false;
	}

	if(m_dirty)
	{
		SqliteMgr::Get()->doUpdate(this);
		m_table->modify();
		m_dirty = false;
	}
}

bool SavableManager::exists()
{
	if(m_newentry)
		return false;

	return true;
}

void SavableManager::bindKeys(sqlite3_stmt* stmt, int startpos) const
{
	int pos = startpos;
	int rc = 0;
	for(Keys::const_iterator it = m_keys.begin(); it != m_keys.end(); it++)
	{
		rc = sqlite3_bind_int64(stmt, pos, *it);
		
		if(rc != SQLITE_OK)
			throw new std::runtime_error("SavableManager::bindLookup(), rc != SQLITE_OK.");
		pos++;
	}
}

void SavableManager::bindFields(sqlite3_stmt* stmt, int startpos) const
{
	int pos = startpos;
	int rc = 0;
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if(it->first->isText())
			rc = sqlite3_bind_text(stmt, pos, it->second->getStringValue().c_str(), it->second->getStringValue().size(), SQLITE_TRANSIENT);
		else
			rc = sqlite3_bind_int64(stmt, pos, it->second->getIntegerValue());
			
		if(rc != SQLITE_OK)
			throw new std::runtime_error("SavableManager::bindLookup(), rc != SQLITE_OK.");
		pos++;
	}
}

void SavableManager::bindUpdate(sqlite3_stmt* stmt) const
{
	bindFields(stmt);
	bindKeys(stmt, m_fields.size() + 1);
}

void SavableManager::bindLookup(sqlite3_stmt* stmt) const
{
	int rc = 0;
	rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);
	if(rc != SQLITE_OK)
		throw new std::runtime_error("SavableManager::bindLookup(), rc != SQLITE_OK.");
}

void SavableManager::parseInsert(sqlite3* db)
{	
	// assert(m_keys.size() == 0);
	Key key(sqlite3_last_insert_rowid(db));
	m_keys.push_back(key);
}

void SavableManager::parseSelect(sqlite3_stmt* stmt)
{
	int pos = 1;
	const unsigned char * text;
	for(Fields::const_iterator it = m_fields.begin(); it != m_fields.end(); it++)
	{
		if(it->first->isText())
		{
			text = sqlite3_column_text(stmt, pos);
			if(text != 0)
			{
				std::string value = std::string((const char *)text);
				it->second->setTextValue(value);
			}
		}
		else
		{
			value_type value =  sqlite3_column_int64(stmt, pos);
			it->second->setIntegerValue(value);
		}
		
		pos++;
	}
	
	m_newentry = false;
}

void SavableManager::parseLookup(sqlite3_stmt* stmt)
{
	// assert(m_keys.size() == 0);
	Key key(sqlite3_column_int64(stmt, 0));
	m_keys.push_back(key);
}

TablePtr SavableManager::getTable() const
{
	return m_table;
}

const Keys& SavableManager::getkeys() const
{
	return m_keys;
}

ValuePtr SavableManager::getfield(FieldImplPtr field) const
{
	Fields::const_iterator it = m_fields.find(field);
	if(it != m_fields.end())
		return it->second;
	else
		throw std::invalid_argument("SavableManager::getfield(), field not in m_fields.");
}

void SavableManager::setkeys(Keys keys)
{
	if(keys.size() != m_table->keysize())
		throw std::invalid_argument("SavableManager::setkeys(), key sizes don't match.");
		
	m_keys = keys;
}

void SavableManager::setvalue(ValuePtr value)
{
	if(!m_table->hasfield(value->getField()))
		throw std::invalid_argument("SavableManager::setfield(), field not in m_table.");
	
	m_fields[value->getField()] = value;
}
