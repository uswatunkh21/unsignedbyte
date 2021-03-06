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

#include "SavableHeaders.h"

#include "Global.h"
#include "Editor.h"
#include "Interpreter.h"
#include "CommandObject.h"

class OLCEditor : public Editor
{
public:
	typedef CommandObject<OLCEditor> SavableCommand;

	OLCEditor(UBSocket* sock) : Editor(sock) {};
	virtual ~OLCEditor(void) {};
	
	virtual std::string lookup(const std::string& action);
	virtual void dispatch(const std::string& action, const std::string& argument);
	
	virtual SavablePtr getEditing() = 0;
	virtual TableImplPtr getTable() = 0;
	virtual KeysPtr addNew() = 0;

	virtual std::vector<std::string> getList() = 0;
	virtual std::vector<std::string> getCommands() = 0;
	
	virtual void setEditing(KeysPtr keys) = 0;
	
	void listCommands(const std::string& argument);
	void newSavable(const std::string& argument);
	void deleteSavable(const std::string& argument);
	void editSavable(const std::string& argument);
	void quitEditor(const std::string& argument);
	void doneEditing(const std::string& argument);
	void listSavable(const std::string& argument);
	
private:
	OLCEditor(const OLCEditor& rhs) : Editor(rhs.m_sock) {};
	
protected:	
	class GeneralInterpreter : public Interpreter<SavableCommand>, public Singleton<GeneralInterpreter> {
	private:
		GeneralInterpreter(void);
		~GeneralInterpreter(void);
		friend class Singleton<GeneralInterpreter>;
	};
	
	static SavableCommand m_listCommands;
	static SavableCommand m_newSavable;
	static SavableCommand m_deleteSavable;
	static SavableCommand m_editSavable;
	static SavableCommand m_quitEditor;
	static SavableCommand m_doneEditing;
	static SavableCommand m_listSavable;
};
