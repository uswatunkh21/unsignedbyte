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

#include "Types.h"

#include <fstream>

class ClassSourceGenerator
{
public:
	ClassSourceGenerator(TableDefPtr table, std::ofstream* file);
	~ClassSourceGenerator();
	
	void GenerateClass();

private:
	ClassSourceGenerator(const ClassSourceGenerator& rhs) : m_table(rhs.m_table) { };
	ClassSourceGenerator operator=(const ClassSourceGenerator& rhs) { return *this; };
	
	void AppendHeader();
	void AppendCtorGeneral();
	void AppendCtorDtor();
	void AppendKeyFactory();
	void AppendCtorFactory();
	void AppendBody();
	void AppendBindKeys();
	void AppendBindUpdate();
	void AppendBindLookup();
	void AppendParseInsert();
	void AppendParseSelect();
	void AppendParseLookup();
	void AppendGetTable();
	void AppendGetSet();
	void AppendFooter();
	
	std::string m_tabs;
	TableDefPtr m_table;
	std::ofstream* m_file;
	std::string m_name;
};
