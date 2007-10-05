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

#include <stdexcept>

#include "ClassSourceGenerator.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "Field.h"
#include "StringUtilities.h"

using std::endl;

ClassSourceGenerator::ClassSourceGenerator(TablePtr table, std::ofstream* file) :
m_tabs("\t"),
m_table(table),
m_file(file),
m_name(m_table->tableName())
{

}

ClassSourceGenerator::~ClassSourceGenerator()
{

}

void ClassSourceGenerator::GenerateClass()
{
	if(m_table->keysize() == 0)
		throw std::logic_error("ClassSourceGenerator::GenerateClass(), class has no primary keys!");
		
	try
	{
		AppendHeader();
		AppendCtorGeneral();
		AppendCtorDtor();
		AppendKeyFactory();
		AppendCtorFactory();
		AppendBody();
		AppendBindKeys();
		AppendBindUpdate();
		AppendBindLookup();
		AppendParseInsert();
		AppendParseSelect();
		AppendParseLookup();
		AppendGetTable();
		AppendGetSet();
		AppendFooter();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		Global::Get()->bugf("Could not generate class '%s'.", m_name.c_str());
	}
}

void ClassSourceGenerator::AppendHeader()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * Begin of implementation" << endl;
	(*m_file) << " * class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceGenerator::AppendCtorGeneral()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
			
	// Empty constructor
	(*m_file) << "// Ctors" << endl;
	(*m_file) << m_name << "::" << m_name << "() :" << endl;
	(*m_file) << "m_" << m_table->firstKey() << "()";
		
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		(*m_file) << "," << endl;
		if((*it)->isText())
			(*m_file) << "m_" << (*it)->getName() << "()";
		else
			(*m_file) << "m_" << (*it)->getName() << "(0)";
	}
	(*m_file) << endl;
	
	(*m_file) << "{" << endl;
	(*m_file) << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendCtorDtor()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	// Destructor
	(*m_file) << m_name << "::~" << m_name << "()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	return;
}

void ClassSourceGenerator::AppendKeyFactory()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	// Specific constructor
	(*m_file) << m_name << "* " << m_name << "::bykey(";

	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		if(it != m_table->keybegin())
			(*m_file) << ", ";
		
		(*m_file) << "value_type " << it->first;
	}

	(*m_file) << ")" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << m_name << "* result = new " << m_name << "();" << endl;
		
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
		(*m_file) << m_tabs << "result->m_" << it->first << " = " << it->first<< ";" << endl;
	
	(*m_file) << m_tabs << "SqliteMgr::Get()->doSelect(result);" << endl;
	(*m_file) << m_tabs << "return result;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendCtorFactory()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	if(m_table->lookupsize() == 0)
		return;
		
	for(Fields::const_iterator it = m_table->lookupbegin(); it != m_table->lookupend(); it++)
	{
		(*m_file) << m_name << "* " << m_name << "::by" << (*it)->getName() << "(";
		if((*it)->isText())
			(*m_file) << "const std::string& value)" << endl;
		else
			(*m_file) << "value_type value);" << endl;
		(*m_file) << "{" << endl;
		(*m_file) << m_tabs << m_name << "* result = new " << m_name << "();" << endl;
		(*m_file) << m_tabs << "result->m_lookupvalue = value;" << endl;
		(*m_file) << m_tabs << "SqliteMgr::Get()->doLookup(result,\"" << (*it)->getName() << "\");" << endl;
		(*m_file) << m_tabs << "return result;" << endl;
		(*m_file) << "}" << endl;
		(*m_file) << endl;
	}
	
	if(m_table->hasSinglularPrimaryKey())
	{	
		for(Fields::const_iterator it = m_table->lookupbegin(); it != m_table->lookupend(); it++)
		{
			(*m_file) << "value_type " << m_name << "::lookup" << (*it)->getName() << "(";
			if((*it)->isText())
				(*m_file) << "const std::string& value)" << endl;
			else
				(*m_file) << "value_type value)" << endl;
			(*m_file) << "{" << endl;
			
			(*m_file) << m_tabs <<  m_name << "* result = new " << m_name << "();" << endl;
			(*m_file) << m_tabs << "SmartPtr<Bindable> bindableresult(result); // will handle deletion of ptr" << endl;
			(*m_file) << m_tabs << "result->m_lookupvalue = value;" << endl;
			(*m_file) << m_tabs << "value_type key = 0;" << endl;
			(*m_file) << m_tabs << "try {" << endl;
			(*m_file) << m_tabs << m_tabs << "SqliteMgr::Get()->doLookup(bindableresult, \"" << (*it)->getName() << "\");" << endl;
			(*m_file) << m_tabs << m_tabs << "key = result->get" << m_table->firstKey() << "();" << endl;
			(*m_file) << m_tabs << "} catch(SmartPtr<Bindable> result) {	}" << endl;
			(*m_file) << endl;
			(*m_file) << m_tabs << "return key;" << endl;
			(*m_file) << "}" << endl;
			(*m_file) << endl;
		}
	}
}

void ClassSourceGenerator::AppendBody()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_name <<  "::erase()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "if(!m_newentry)" << endl;	
	(*m_file) << m_tabs << m_tabs << "SqliteMgr::Get()->doErase(this);" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
		
	(*m_file) << "void " << m_name << "::save()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "if(m_newentry)" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << m_tabs << "SqliteMgr::Get()->doInsert(this);" << endl;
	(*m_file) << m_tabs << m_tabs << "m_newentry = false;" << endl;
	(*m_file) << m_tabs << "}" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "if(m_dirty)" << endl;
	(*m_file) << m_tabs << "{" << endl;
	(*m_file) << m_tabs << m_tabs << "SqliteMgr::Get()->doUpdate(this);" << endl;
	(*m_file) << m_tabs << m_tabs << "getTable()->modify();" << endl;
	(*m_file) << m_tabs << m_tabs << "m_dirty = false;" << endl;
	(*m_file) << m_tabs << "}" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
	
	(*m_file) << "bool " << m_name <<  "::exists()" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "if(m_newentry)" << endl;	
	(*m_file) << m_tabs << m_tabs << "return false;" << endl;
	(*m_file) << endl;
	(*m_file) << m_tabs << "return true;" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBindKeys()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	
	(*m_file) << "void " << m_name << "::bindKeys(sqlite3_stmt* stmt) const" << endl;
	(*m_file) << "{" << endl;
	int pos = 1;
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << m_tabs << "sqlite3_bind_int64(stmt, " << pos; 
		(*m_file) << ", m_" << it->first << ");" << endl;
		pos++;
	}

	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBindUpdate()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "void " << m_name << "::bindUpdate(sqlite3_stmt* stmt) const" << endl;
	(*m_file) << "{" << endl;
	
	int pos = 1;
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		if((*it)->isText())
		{
			(*m_file) << m_tabs << "sqlite3_bind_text(stmt, " << pos;
			(*m_file) << ", m_" << (*it)->getName() <<".c_str(), m_" << (*it)->getName() << ".size(), SQLITE_TRANSIENT);";
			(*m_file) << endl;
		}
		else
		{
			(*m_file) << m_tabs << "sqlite3_bind_int64(stmt, " << pos << ", m_" << (*it)->getName() << ");" << endl;
		}
		pos++;
	}

	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << m_tabs << "sqlite3_bind_int64(stmt, " << pos; 
		(*m_file) << ", m_" << it->first << ");" << endl;
		pos++;
	}

	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendBindLookup()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "void " << m_name << "::bindLookup(sqlite3_stmt* stmt) const" << endl;
	(*m_file) << "{" << endl;
	if(m_table->lookupsize())
	{
		(*m_file) << m_tabs << "int rc;" << endl;
		(*m_file) << m_tabs << "rc = sqlite3_bind_text(stmt, 1, m_lookupvalue.c_str(), m_lookupvalue.size(), SQLITE_TRANSIENT);" << endl;
		(*m_file) << m_tabs << "if(rc != SQLITE_OK)" << endl;
		(*m_file) << m_tabs << m_tabs << "throw new std::runtime_error(\"SqliteMgr::bindLookup(), rc != SQLITE_OK.\");" << endl;
	}
	else
	{
		(*m_file) << m_tabs << "// Do nothing" << endl;
	}
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendParseInsert()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "void " << m_name << "::parseInsert(sqlite3* db)" << endl;
	(*m_file) << "{" << endl;

	if(m_table->hasSinglularPrimaryKey())
		(*m_file) << m_tabs << "m_" << m_table->firstKey() << " = sqlite3_last_insert_rowid(db);" << endl;
	else
		(*m_file) << m_tabs << "// Do nothing" << endl;
		
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendParseSelect()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	bool hasText = false;
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		if((*it)->isText())
		{
			hasText = true;
			break;
		}
	}
	
	(*m_file) << "void " << m_name << "::parseSelect(sqlite3_stmt* stmt)" << endl;
	(*m_file) << "{" << endl;
	
	if(hasText)
		(*m_file) << m_tabs << "const unsigned char * text;" << endl;

	int count = 0;
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		if((*it)->isText())
		{
			(*m_file) << m_tabs << "text = sqlite3_column_text(stmt, " << count << ");" << endl;
			(*m_file) << m_tabs << "m_" << (*it)->getName() << " = ";
			(*m_file) << "std::string((const char *)text);" << endl;
		}
		else
		{
			(*m_file) << m_tabs << "m_" << (*it)->getName() << " = ";
			(*m_file) << "sqlite3_column_int64(stmt, " << count << ");" << endl;
		}

		count++;
	}
	
	if(count)
		(*m_file) << m_tabs << "m_newentry = false;" << endl;
	else
		(*m_file) << m_tabs << "// Do nothing" << endl;
		
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}
	
void ClassSourceGenerator::AppendParseLookup()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	(*m_file) << "void " << m_name << "::parseLookup(sqlite3_stmt* stmt)" << endl;
	(*m_file) << "{" << endl;
	
	int count = 0;
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << m_tabs << "m_" << it->first << " = sqlite3_column_int64(stmt, " << count << ");" << endl; 
		count++;
	}
	
	if(!count)
		(*m_file) << m_tabs << "// Do nothing" << endl;
		
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}	
		
void ClassSourceGenerator::AppendGetTable()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << "TablePtr " << m_name << "::getTable() const" << endl;
	(*m_file) << "{" << endl;
	(*m_file) << m_tabs << "return Tables::Get()->";
	(*m_file) << String::Get()->toupper(m_name);
	(*m_file) << ";" << endl;
	(*m_file) << "}" << endl;
	(*m_file) << endl;
}

void ClassSourceGenerator::AppendGetSet()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
		
	for(TableMap::const_iterator it = m_table->keybegin(); it != m_table->keyend(); it++)
	{
		(*m_file) << "value_type " << m_name <<"::get" << it->first << "() const" << endl;
		(*m_file) << "{" << endl;
		(*m_file) << m_tabs << "return m_" << it->first << ";" << endl;
		(*m_file) << "}" << endl;
		(*m_file) << endl;
	}
		
	// Getters
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		FieldPtr field = *it;
		if(field->isText())
			(*m_file) << "const std::string& " << m_name <<"::get" << field->getName() << "() const" << endl;
		else
			(*m_file) << "value_type " << m_name << "::get" << field->getName() << "() const" << endl;
			
		(*m_file) << "{" << endl;
		(*m_file) << m_tabs << "return m_" << field->getName() << ";" << endl;
		(*m_file) << "}" << endl;
		(*m_file) << endl;
	}

	// Setters
	for(Fields::const_iterator it = m_table->begin(); it != m_table->end(); it++)
	{
		FieldPtr field = *it;
		if(field->isText())
			(*m_file) << "void " << m_name << "::set" << field->getName() << "(const std::string& value)" << endl;
		else
			(*m_file) << "void " << m_name << "::set" << field->getName() << "(value_type value)" << endl;
			
		(*m_file) << "{" << endl;
		(*m_file) << m_tabs << "m_" << field->getName() << " = value;" << endl;
		(*m_file) << m_tabs << "m_dirty = true;" << endl;
		(*m_file) << "}" << endl;
		(*m_file) << endl;
	}
}

void ClassSourceGenerator::AppendFooter()
{
	if(!m_file)
		throw std::logic_error("Source file is not open for writing.\n");
	
	(*m_file) << endl;
	(*m_file) << "/**" << endl;
	(*m_file) << " * End of implementation" << endl;
	(*m_file) << " * class " << m_name << endl;
	(*m_file) << " **/" << endl;
	(*m_file) << endl;

	return;
}
