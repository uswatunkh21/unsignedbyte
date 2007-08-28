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

#include <string>
#include <vector>
#include <stdexcept>

#include "Initializer.h"
#include "sqlite3.h"
#include "Database.h"
#include "Query.h"
#include "Global.h"
#include "Tables.h"
#include "Table.h"
#include "hp.h"

bool Initializer::DatabasePopulated()
{
	Query q(*m_db);
	q.get_result("SELECT * FROM SQLITE_MASTER;");
	
	bool populated = false;
	
	if(q.fetch_row())
		populated = true;
		
	q.free_result();
	return populated;
}

bool Initializer::VerifyDatabaseVersion()
{
	try
	{
		// hp::Version ver(m_db, 1);
		
		return true;
	}
	catch(std::runtime_error& e)
	{
		Global::Get()->bug(e.what());
		return false;
	}
}

void Initializer::InitTables()
{
	Query q(*m_db);
	
	for(TableVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = (*it)->creationQuery();
		Global::Get()->logf("%s\n", sql.c_str());
		q.execute(sql);
	}
	
	return;
}

bool Initializer::VerifyTables()
{
	bool good = true;
	
	Query q(*m_db);
	for(TableVector::const_iterator it = Tables::Get()->begin(); it != Tables::Get()->end(); it++)
	{
		std::string sql = (*it)->tableQuery();
		std::string result = q.get_string(sql);
		if(result.compare("table"))
		{
			Global::Get()->bugf("Table %s's creation query does not match the one from the input database!\n", sql.c_str());
			good = false;
		}
	}
	
	return good;
}

void Initializer::InitDatabase()
{
	Query q(*m_db);
	q.execute(Global::Get()->sprintf(
		"INSERT OR REPLACE INTO %s(%s, versiontext, major, minor, micro)"
		" values(1"
		",'%s'"
		", %d"
		", %d"
		", %d"
		");",
		Tables::Get()->VERSION->tableName().c_str(),
		Tables::Get()->VERSION->tableID().c_str(),
		game::vstring,
		game::major,
		game::minor,
		game::micro
		));

	q.execute(Global::Get()->sprintf(
		"INSERT OR REPLACE INTO %s(%s, name, password)"
		" values(1"
		", '%s'"
		", 'qq'"
		");",
		Tables::Get()->ACCOUNTS->tableName().c_str(),
		Tables::Get()->ACCOUNTS->tableID().c_str(),
		game::vname
		));
}

void Initializer::InitColours()
{
	std::string sql = Global::Get()->sprintf(
		"INSERT OR IGNORE INTO %s(%s, name, code, colourstring, ansi)"
		" values(?, ?, ?, ?, 1);",
		Tables::Get()->COLOURS->tableName().c_str(),
		Tables::Get()->COLOURS->tableID().c_str());

	sqlite3_stmt* res; // pointer to the result
	const char* tailer = NULL; // pointer to a constant char array

	Database::OPENDB* db = m_db->grabdb();
	if(!db)
	{
		printf("Could not open database!\n");
		return;
	}

	int rc = sqlite3_prepare_v2(db->db, sql.c_str(), (int)sql.size(), &res, &tailer);
	if (rc != SQLITE_OK)
	{
		printf("Prepare Query Failed: '%s'", sql.c_str());
		return;
	}
	
	const struct colour colours[] = 
	{
		{ "Restore", "^", "0;0m" },
		{ "Dark Red", "r", "31m" },
		{ "Dark Green", "g", "32m" },
		{ "Dark Yellow", "y", "33m"},
		{ "Dark Blue", "b", "34m" },
		{ "Dark Purple", "m", "35m" },
		{ "Dark Cyan", "c", "36m" },
		{ "Gray", "w", "37m" },
		{ "Black", "l", "30m" },
		// Light colours
		{ "Light Red", "R", "1;31m" },
		{ "Light blue", "G", "1;32m" },
		{ "Light Yellow", "Y", "1;33m" },
		{ "Light Blue", "B", "1;34m" },
		{ "Light Magenta", "M", "1;35m" },
		{ "Light Cyan", "C", "1;36m" },
		{ "White", "W", "1;37m" },
		{ "Gray", "L", "1;30m" },
	};
	
	int size = sizeof(colours) / sizeof(colours[0]);

	for(int i = 0; i < size; i++)
	{
		rc = sqlite3_bind_int(res, 1, i+2);
		if(rc != SQLITE_OK) printf("sqlite3_bind_int returned %d at iteration %d.\n", rc, i);
		rc = sqlite3_bind_text(res, 2, colours[i].name.c_str(), -1 , SQLITE_TRANSIENT);
		if(rc != SQLITE_OK) Global::Get()->bugf("DatabaseMgr::InitColours(), sqlite3_bind_text(2) returned %d at iteration %d.\n", rc, i);
		rc = sqlite3_bind_text(res, 3, colours[i].code.c_str(), -1, SQLITE_TRANSIENT);
		if(rc != SQLITE_OK) Global::Get()->bugf("DatabaseMgr::InitColours(), sqlite3_bind_text(3) returned %d at iteration %d.\n", rc, i);
		rc = sqlite3_bind_text(res, 4, colours[i].cstr.c_str(), -1, SQLITE_TRANSIENT);
		if(rc != SQLITE_OK) Global::Get()->bugf("DatabaseMgr::InitColours(), sqlite3_bind_text(4) returned %d at iteration %d.\n", rc, i);
		rc = sqlite3_step(res);
		if(rc != SQLITE_DONE) Global::Get()->bugf("DatabaseMgr::InitColours(), sqlite3_step returned %d at iteration %d.\n", rc, i);
		rc = sqlite3_reset(res);
		if(rc != SQLITE_OK) Global::Get()->bugf("DatabaseMgr::InitColours(), sqlite3_reset returned %d at iteration %d.\n", rc, i);
	}

	sqlite3_finalize(res); // deallocate statement
	m_db->freedb(db);
}