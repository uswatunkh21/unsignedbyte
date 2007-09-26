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
#include <fstream>
#include <smart_ptr.h>

class Table;
typedef SmartPtr<Table> TablePtr;

class ClassHeaderGenerator
{
public:
	ClassHeaderGenerator(TablePtr table, std::ofstream* file);
	~ClassHeaderGenerator();
	
	void GenerateClass();

private:
	ClassHeaderGenerator(const ClassHeaderGenerator& rhs) : m_table(rhs.m_table) { };
	ClassHeaderGenerator operator=(const ClassHeaderGenerator& rhs) { return *this; };
	
	void AppendHeader();
	void AppendCtor();
	void AppendFields();
	void AppendBody();
	void AppendFooter();
	
	std::string m_tabs;
	TablePtr m_table;
	std::ofstream* m_file;
};
