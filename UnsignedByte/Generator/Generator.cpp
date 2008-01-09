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

#include "Generator.h"
#include "Global.h"
#include "Tables.h"
#include "TableDef.h"
#include "StringUtilities.h"

#include "ClassHeaderGenerator.h"
#include "ClassSourceGenerator.h"

using std::endl;

Generator::Generator(const std::string name) :
m_name(name),
m_tabs("\t")
{
	std::string headername;
	#ifdef _WIN32
	headername.append("../include/");
	#endif
	headername.append(m_name);
	headername.append(".h");
	m_headerfile.open(headername.c_str());
	
	std::string sourcename;
	#ifdef _WIN32
	sourcename.append("../DAL/");
	#endif
	sourcename.append(m_name);
	sourcename.append(".cpp");
	m_sourcefile.open(sourcename.c_str());
}

Generator::~Generator()
{
	if(m_headerfile.is_open())
		m_headerfile.close();

	if(m_sourcefile.is_open())
		m_sourcefile.close();
}

bool Generator::GenerateDAL()
{
	try
	{
		CreateHeader();
		CreateSource();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		Global::Get()->bug("Could not generate DAL.\n");
		return false;	
	}
	
	return true;
}

void Generator::AppendLicense(std::ofstream& file)
{
	if(!file)
		throw std::logic_error("File is not open for writing.\n");
		
	file << "/***************************************************************************" << endl;
	file << " *   Copyright (C) 2007 by Sverre Rabbelier                                *" << endl;
	file << " *   sverre@rabbelier.nl                                                   *" << endl;
	file << " *                                                                         *" << endl;
	file << " *   This program is free software; you can redistribute it and/or modify  *" << endl;
	file << " *   it under the terms of the GNU General Public License as published by  *" << endl;
	file << " *   the Free Software Foundation; either version 3 of the License, or     *" << endl;
	file << " *   (at your option) any later version.                                   *" << endl;
	file << " *                                                                         *" << endl;
	file << " *   This program is distributed in the hope that it will be useful,       *" << endl;
	file << " *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *" << endl;
	file << " *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *" << endl;
	file << " *   GNU General Public License for more details.                          *" << endl;
	file << " *                                                                         *" << endl;
	file << " *   You should have received a copy of the GNU General Public License     *" << endl;
	file << " *   along with this program; if not, write to the                         *" << endl;
	file << " *   Free Software Foundation, Inc.,                                       *" << endl;
	file << " *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *" << endl;
	file << " ***************************************************************************/" << endl;
	file << endl;
	
	return;
}

void Generator::AppendHeaderIncludes()
{
	if(!m_headerfile)
		throw std::logic_error("Header file is not open for writing.\n");
	
	m_headerfile << "#pragma once" << endl;
	m_headerfile << "#ifdef _WIN32" << endl;
	m_headerfile << m_tabs << "#pragma warning (disable:4800)" << endl;
	m_headerfile << "#endif" << endl;
	m_headerfile << endl;
	
	m_headerfile << "#include \"Types.h\"" << endl;
	m_headerfile << endl;
	m_headerfile << "#include <Database.h>" << endl;
	m_headerfile << "#include <SqliteMgr.h>" << endl;
	m_headerfile << "#include <Bindable.h>" << endl;
	m_headerfile << endl;
	
	m_headerfile << "namespace " << m_name << endl;
	m_headerfile << "{" << endl;
	
	return;
}

void Generator::AppendHeaderTableImpls()
{
	m_headerfile << m_tabs << "class TableImpls : public Singleton<TableImpls>" << endl;
	m_headerfile << m_tabs << "{" << endl;
	m_headerfile << m_tabs << "public:" << endl;
	
	for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		TableDefPtr table = *it;
		m_headerfile << m_tabs << m_tabs << "TableImplPtr " << String::Get()->toupper(table->tableName()) << ";" << endl;
	}
	m_headerfile << endl;
	m_headerfile << m_tabs << m_tabs << "TableImplVector::const_iterator begin() const { return m_tables.begin(); }" << endl;
	m_headerfile << m_tabs << m_tabs << "TableImplVector::const_iterator end() const { return m_tables.end(); }" << endl;
	m_headerfile << endl;
	
	m_headerfile << m_tabs << "private:" << endl;
	m_headerfile << m_tabs << m_tabs << "TableImpls();" << endl;
	m_headerfile << m_tabs << m_tabs << "~TableImpls() { }" << endl;
	m_headerfile << m_tabs << m_tabs << "TableImpls(const TableImpls& rhs);" << endl;
	m_headerfile << m_tabs << m_tabs << "TableImpls operator=(const TableImpls& rhs);" << endl;
	m_headerfile << m_tabs << m_tabs << "friend class Singleton<TableImpls>;" << endl;
	m_headerfile << endl;
	m_headerfile << m_tabs << m_tabs << "TableImplVector m_tables;" << endl;
	m_headerfile << m_tabs << "};" << endl;
	m_headerfile << endl;
}

void Generator::AppendHeaderClass(TableDefPtr table)
{
	try
	{
		ClassHeaderGenerator gen(table, &m_headerfile);
		gen.GenerateClass();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not append constructor declaration to header file.\n");
	}
	
	return;
}

void Generator::AppendHeaderFooter()
{
	if(!m_headerfile)
		throw std::logic_error("Header file is not open for writing.\n");
	
	m_headerfile << "} // end of namespace" << endl;
	m_headerfile << endl;
	
	return;
}

void Generator::CreateHeader()
{
	try
	{
		AppendLicense(m_headerfile);
		AppendHeaderIncludes();
		AppendHeaderTableImpls();
		
		for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
			AppendHeaderClass(*it);
			
		AppendHeaderFooter();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not create header file.\n");
	}
	
	return;
}

void Generator::AppendSourceIncludes()
{
	if(!m_sourcefile)
		throw std::logic_error("Header file is not open for writing.\n");

	m_sourcefile << "#ifdef _WIN32" << endl;
	m_sourcefile << "#pragma warning (disable:4244)" << endl;
	m_sourcefile << "#pragma warning (disable:4267)" << endl;
	m_sourcefile << "#endif" << endl;
	m_sourcefile << endl;
	
	m_sourcefile << "#include \"" << m_name << ".h\"" << endl;
	m_sourcefile << endl;
	
	m_sourcefile << "#include <Database.h>" << endl;
	m_sourcefile << "#include <Query.h>" << endl;
	m_sourcefile << endl;
	
	m_sourcefile << "#include \"TableImpl.h\"" << endl;
	m_sourcefile << "#include \"Tables.h\"" << endl;
	m_sourcefile << "#include \"FieldImpl.h\"" << endl;
	m_sourcefile << "#include \"KeyDef.h\"" << endl;
	m_sourcefile << endl;
	
	m_sourcefile << "using namespace " << m_name << ";" << endl;
	m_sourcefile << endl;
	
	return;
}

void Generator::AppendSourceClass(TableDefPtr table)
{
	try
	{
		ClassSourceGenerator gen(table, &m_sourcefile);
		gen.GenerateClass();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not append constructor declaration to header file.\n");
	}
	
	return;
}

void Generator::AppendSourceFooter()
{
	if(!m_sourcefile)
		throw std::logic_error("Header file is not open for writing.\n");
	
	m_headerfile << endl;
	
	return;
}

void Generator::AppendSourceTableImpls()
{
	m_sourcefile << "TableImpls::TableImpls() :" << endl;
	for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		if(it != Tables::Get()->begin())
			m_sourcefile << "," << endl;
		
		TableDefPtr table = *it;
		m_sourcefile << String::Get()->toupper(table->tableName()) << "(new TableImpl(Tables::Get()->" << String::Get()->toupper(table->tableName()) << ", \"" << table->tableName() << "\"))";
	}
	
	m_sourcefile << endl;
	m_sourcefile << "{" << endl;
	for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		m_sourcefile << m_tabs << "m_tables.push_back(" << String::Get()->toupper((*it)->tableName()) << ");" << endl;
	}
	m_sourcefile << "}" << endl;
	m_sourcefile << endl;
}

void Generator::CreateSource()
{
	try
	{
		AppendLicense(m_sourcefile);
		AppendSourceIncludes();
		AppendSourceTableImpls();
		
		for(TableDefVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
			AppendSourceClass(*it);
			
		AppendSourceFooter();
	}
	catch(std::logic_error& e)
	{
		Global::Get()->bug(e.what());
		throw std::logic_error("Could not create source file.\n");
	}
	
	return;
}
