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
#include "Editor.h"

namespace mud
{
	class Account;
	typedef SmartPtr<mud::Account> AccountPtr;
	
	class Channel;
	typedef SmartPtr<mud::Channel> ChannelPtr;
}

class EditorAccountLogin : public Editor
{
public:
	EditorAccountLogin(UBSocket* sock);
	~EditorAccountLogin(void);

	void OnLine(const std::string& line);
	std::string name() { return "AccountLogin"; };
	bool canReceiveChannel(mud::ChannelPtr channel) const;
	
private:
	EditorAccountLogin(const EditorAccountLogin& rhs);
	EditorAccountLogin operator=(const EditorAccountLogin& rhs);
	
	enum E_STATE
	{
		M_FIRST,
		M_NAME,
		M_PASSWORD,
	};

	int m_state;
	mud::AccountPtr m_account;
};
