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

#include <vector>
#include <string>

#include "EditorChunk.h"
#include "EditorOLC.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Account.h"
#include "Chunk.h"
#include "ChunkManager.h"

EditorChunk::ChunkCommand EditorChunk::m_editName("Name", &EditorChunk::editName);
EditorChunk::ChunkCommand EditorChunk::m_editDescription("Description", &EditorChunk::editDescription);
EditorChunk::ChunkCommand EditorChunk::m_showChunk("Show", &EditorChunk::showChunk);
EditorChunk::ChunkCommand EditorChunk::m_saveChunk("Save", &EditorChunk::saveChunk);

EditorChunk::EditorChunk(UBSocket* sock) :
OLCEditor(sock),
m_chunk()
{
	listCommands(Global::Get()->EmptyString);
}

EditorChunk::~EditorChunk(void)
{

}

std::string EditorChunk::lookup(const std::string& action)
{
	std::string name = OLCEditor::lookup(action);
	if(name.size() != 0)
		return name;
		
	ChunkCommand* act = ChunkInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorChunk::dispatch(const std::string& action, const std::string& argument)
{
	ChunkCommand* act = ChunkInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(this, argument);
	else
		OLCEditor::dispatch(action, argument);
		
	return;
}

SavablePtr EditorChunk::getEditing()
{
	return m_chunk;
}

TablePtr EditorChunk::getTable()
{
	return Tables::Get()->AREAS;
}

long EditorChunk::addNew()
{
	return mud::ChunkManager::Get()->Add();
}

std::vector<std::string> EditorChunk::getList()
{
	return mud::ChunkManager::Get()->List();
}

void EditorChunk::setEditing(long id)
{
	if(id == 0)
	{
		m_chunk.reset();
		return;
	}
	
	m_chunk = mud::ChunkManager::Get()->GetByKey(id);
	return;
}

std::vector<std::string> EditorChunk::getCommands()
{
	return ChunkInterpreter::Get()->getWords();
}

EditorChunk::ChunkInterpreter::ChunkInterpreter(void)
{
	addWord("name", &m_editName);
	addWord("description", &m_editDescription);
	addWord("show", &m_showChunk);
	addWord("save", &m_saveChunk);
}

EditorChunk::ChunkInterpreter::~ChunkInterpreter(void)
{

}

void EditorChunk::editName(const std::string& argument)
{
	if(argument.size() == 0)
	{
		m_sock->Send("Chunk name can't be zero length!\n");
		return;
	}

	m_sock->Sendf("Chunk name changed from '%s' to '%s'.\n", m_chunk->getName().c_str(), argument.c_str());
	m_chunk->setName(argument);
	return;
}

void EditorChunk::editDescription(const std::string& argument)
{
	if(!m_chunk->Exists())
	{
		m_sock->Send("For some reason the chunk you are editing does not exist.\n");
		return;
	}

	if(argument.size() == 0)
	{
		m_sock->Send("No argument, dropping you into the string editor!\n");
		return;
	}

	m_sock->Sendf("Chunk description changed from '%s' to '%s'.\n", m_chunk->getDescription().c_str(), argument.c_str());
	m_chunk->setDescription(argument);
	return;
}

void EditorChunk::showChunk(const std::string& argument)
{
	m_sock->Send(String::Get()->box(m_chunk->Show(), "Chunk"));
}

void EditorChunk::saveChunk(const std::string& argument)
{
	m_sock->Sendf("Saving chunk '%s'.\n", m_chunk->getName().c_str());
	m_chunk->Save();
	m_sock->Send("Saved.\n");
	return;
}