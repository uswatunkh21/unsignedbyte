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

namespace mud
{
	class Account;
	typedef SmartPtr<Account> AccountPtr;
	
	class Channel;
	typedef SmartPtr<Channel> ChannelPtr;
	
	class Account : public Savable
	{
	public:
		/**
		 * \brief Getters
		 */
		value_type getID() const;
		const std::string& getName() const;
		const std::string& getPassword() const;
		bool wantReceiveChannel(ChannelPtr channel) const;

		/**
		 * \brief Setters
		 */
		void setName(const std::string& name);
		void setPassword(const std::string& password);

		/**
		 * \brief Utilities
		 */
		std::vector<std::string> Show();
		std::string ShowShort();
		TableImplPtr getTable() const;
			
		/**
		 * \brief Database operations
		 */
		void Delete();
		void Save();
		bool Exists();

	private:
		SavableManagerPtr m_account;

		/**
		 * \brief Ctors
		 */
		Account(SavableManagerPtr account);	
		Account(const Account& rhs);
		Account operator=(const Account& rhs);
		~Account(void);
		
		friend class AccountManager; // for constructor
		friend SmartPtrDelete(mud::Account);
	};
}
