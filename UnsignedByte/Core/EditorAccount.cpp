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

#include "Action.h"
#include "EditorAccount.h"
#include "EditorOLC.h"
#include "EditorNewCharacter.h"
#include "EditorPlaying.h"

#include "UBSocket.h"

#include "Global.h"
#include "DatabaseMgr.h"
#include "Cache.h"
#include "Parse.h"
#include "StringUtilities.h"

#include "Account.h"
#include "Command.h"
#include "Permission.h"
#include "PCharacter.h"
#include "Room.h"

using mud::Cache;

extern bool m_quit;

EditorAccount::EditorAccount(UBSocket* sock) :
Editor(sock)
{
	Commands::Get()->Run(sock, Global::Get()->EmptyString);
}

EditorAccount::~EditorAccount(void)
{

}

std::string EditorAccount::lookup(const std::string& action)
{
	UBAction* act = AccountInterpreter::Get()->translate(action);
	if(act)
		return act->getName();
		
	return Global::Get()->EmptyString;
}

void EditorAccount::dispatch(const std::string& action, const std::string& argument)
{
	UBAction* act = AccountInterpreter::Get()->translate(action);
	
	if(act)
		act->Run(m_sock, argument);
	else
		Global::Get()->bugf("EditorAccount::dispatch(), action '%s' not found (argument '%s')!\n", action.c_str(), argument.c_str());
		
	return;
}

EditorAccount::AccountInterpreter::AccountInterpreter(void)
{
	addWord("new", New::Get());
	addWord("login", Login::Get());
	addWord("commands", Commands::Get());
	addWord("quit", Quit::Get());
	addWord("shutdown", Shutdown::Get());
	addWord("list", List::Get());
	addWord("olc", OLC::Get());

	/*
	addWord("ooc", DoOOC::Get());
	addWord("note", DoNote::Get());
	addWord("help", DoHelp::Get());
	*/
}

EditorAccount::AccountInterpreter::~AccountInterpreter(void)
{
	New::Free();
	Login::Free();
	Commands::Free();
	Quit::Free();
	Shutdown::Free();
	List::Free();
	OLC::Free();
}

void EditorAccount::Login::Run(UBSocket* sock, const std::string &argument)
{
	if(argument.size() == 0)
	{
		sock->Send("Please choose a character:\n");
		EditorAccount::List::Get()->Run(sock,"");
		return;
	}

	if(Cache::Get()->isActive(argument))
	{
		sock->Send("You are already playing that character!\n");
		return;
	}

	int count = DatabaseMgr::Get()->CountSavable(Tables::Get()->CHARACTERS, argument);
	if(count <= 0)
	{
		sock->Sendf("You don't have a character named '%s'!\n", argument.c_str());
		Run(sock, Global::Get()->EmptyString);
		return;
	}

	if(count >= 2)
	{
		sock->Sendf("For some reason there are %d character named '%s' known, please contact administration!\n", count, argument.c_str());
		sock->Send("Disconnecting you now.\n");
		sock->SetCloseAndDelete();
		return;
	}

	int id = Cache::Get()->GetCharacterID(argument);
	if(id <= 0)
	{
		sock->Sendf("Got ID %d, which is <= 0, disconnecting you now.\n", id);
		sock->SetCloseAndDelete();
		return;
	}

	// TODO - Check if isAccount before loading
	mud::PCharacter* Ch = Cache::Get()->LoadPCharacter(sock, id);
	if(!Ch->isAccount(sock->GetAccount()))
	{
		Cache::Get()->ClosePCharacter(id);
		sock->Sendf("You don't have a character named '%s'!\n", argument.c_str());
		Run(sock, Global::Get()->EmptyString);
		return;
	}

	sock->Sendf("Welcome back, %s\n", argument.c_str());
	sock->SetEditor(new EditorPlaying(sock, Ch));
	return;
}

void EditorAccount::List::Run(UBSocket* sock, const std::string &argument)
{
	mud::Account* account = sock->GetAccount();
	if(!account || !account->Exists())
	{
		sock->Send("For some reason your account does not exist?!");
		sock->Send("Closing your connection now.\n");
		sock->SetCloseAndDelete();
		return;
	}
	
	// TODO - add character listing
	/*
	Strings characters = DatabaseMgr::Get()->GetSavable(
		Tables::Get()->CHARACTERS, account->getID(), 
		Tables::Get()->ACCOUNTS->tableID());
	
	if(characters.size() == 0)
	{
		sock->Send("You have no characters yet!\n");
		return;
	}
	
	sock->Send(String::Get()->box(characters));
	*/
	sock->Send("Not yet implemented!");
	sock->Send("\n");
	return;
}

void EditorAccount::Commands::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send(String::Get()->box(AccountInterpreter::Get()->getWords(), "Account"));
	sock->Send("\n");
	return;
}

void EditorAccount::OLC::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into OLC mode!\n");
	sock->SetEditor(new EditorOLC(sock));
	return;
}

void EditorAccount::New::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Dropping you into Character Creation mode!\n");
	sock->SetEditor(new EditorNewCharacter(sock));
	return;
}

void EditorAccount::Quit::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Thank you for visiting.\n");
	sock->SetCloseAndDelete();
	return;
}

void EditorAccount::Shutdown::Run(UBSocket* sock, const std::string &argument)
{
	sock->Send("Shutting down...\n");
	m_quit = true;
	sock->Send("Game will shut down after this loop!\n");
	return;
}
