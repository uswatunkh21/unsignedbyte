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
#include <iostream>

#include "sqlite3.h"
#include "Database.h"
#include "Query.h"
#include "IError.h"
#include "StderrLog.h"
#include "Global.h"
#include "Tables.h"

#include "Generator.h"

void exitfunc()
{
	printf("Freeing global...\n");
	Global::Free();
	printf("Freeing tables...\n");
	Tables::Free();
	printf("Exiting...\n");
	// std::cin.get();
	return;
}

int main()
{
	atexit(exitfunc);
		
	printf("Generating DAL...\n");
	Generator gen(game::vname);
	
	bool succes;
	succes = gen.GenerateDAL();
	if(!succes)
	{
		printf("Could not generate DAL!\n");
		std::cin.get();
		return 1;
	}
	
	return 0;
}
