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

#include "Types.h"

#include <Database.h>
#include <singleton.h>

class Table;
class Statements;
class StatementStrings;
class Actor;

typedef SmartPtr<Actor> ActorPtr;
typedef SmartPtr<Table> TablePtr;
typedef SmartPtr<Statements> StatementsPtr;
typedef SmartPtr<StatementStrings> StatementStringsPtr;

typedef std::map<Table*, StatementsPtr>  TableStatements;
typedef std::map<Table*, StatementStringsPtr>  TableStatementStrings;
typedef unsigned long value_type;

class RowNotFoundException : public std::runtime_error
{
	public:
		RowNotFoundException(const std::string& arg) : std::runtime_error(arg) { }
};

class SqliteMgr : public Singleton<SqliteMgr>
{
	public:
		void doInsert(SavableManager* bindable);
		void doErase(SavableManager* bindable);
		void doUpdate(SavableManager* bindable);
		void doSelect(SavableManagerPtr bindable);
		void doLookup(SavableManagerPtr bindable, FieldPtr field);
		void doForEach(Table* table, Actor& act);
		
		std::string tableQuery(TableDefPtr table) const;
		std::string creationQuery(TableDefPtr table, bool verify = false) const;
		std::string creationString(FieldDefPtr table) const;
	
	private:
		Database* m_db;
		Database::OPENDB* m_odb;
		const char* m_leftover;
		
		TableStatements m_statements;
		TableStatementStrings m_statementstrings;
		
		void commit(Table* table);
		
		StatementsPtr getStatements(Table* table);
		StatementStringsPtr getStatementStrings(Table* table);
		
		sqlite3_stmt* getInsertStmt(Table* table);
		sqlite3_stmt* getEraseStmt(Table* table);
		sqlite3_stmt* getUpdateStmt(Table* table);
		sqlite3_stmt* getSelectStmt(Table* table);
		sqlite3_stmt* getLookupStmt(Table* table, FieldPtr field);
		sqlite3_stmt* getForEachStmt(Table* table);		
		
		friend class Singleton<SqliteMgr>;
		SqliteMgr();
		~SqliteMgr();
		bool doStatement(sqlite3_stmt* stmt);
};
