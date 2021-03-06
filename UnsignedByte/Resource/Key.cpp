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

#include "Key.h"
#include "KeyDef.h"
#include "TableImpl.h"
#include "FieldImpl.h"

Key::Key(KeyDefPtr key, value_type value) : 
m_key(key), 
m_value(value),
m_dirty(false)
{ 
	Assert(key); 
}

Key::~Key() 
{ 
	
}
	
KeyDefPtr Key::getKeyDef() const 
{ 
	return m_key; 
}

value_type Key::getValue() const 
{ 
	return m_value; 
}

TableImplPtr Key::getTable() const
{
	return m_key->getTable();
}

bool Key::isDirty() const
{
	return m_dirty;
}

void Key::setDirty(bool dirty)
{
	m_dirty = dirty;
}
