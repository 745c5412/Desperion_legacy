/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

	Desperion is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Desperion is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FIGHT_OPTIONS_INFORMATIONS__
#define __FIGHT_OPTIONS_INFORMATIONS__

class FightOptionsInformations : public DofusModel
{
public:
	bool isSecret;
	bool isRestrictedToPartyOnly;
	bool isClosed;
	bool isAskingForHelp;

	uint16 GetProtocol() const
	{ return FIGHT_OPTIONS_INFORMATIONS; }

	FightOptionsInformations()
	{
	}

	FightOptionsInformations(bool isSecret, bool isRestrictedToPartyOnly, bool isClosed, bool isAskingForHelp) : isSecret(isSecret), isRestrictedToPartyOnly(isRestrictedToPartyOnly), isClosed(isClosed), isAskingForHelp(isAskingForHelp)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, isSecret);
		BooleanByteWrapper::SetFlag(b, 1, isRestrictedToPartyOnly);
		BooleanByteWrapper::SetFlag(b, 2, isClosed);
		BooleanByteWrapper::SetFlag(b, 3, isAskingForHelp);
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		isSecret = BooleanByteWrapper::GetFlag(b, 0);
		isRestrictedToPartyOnly = BooleanByteWrapper::GetFlag(b, 1);
		isClosed = BooleanByteWrapper::GetFlag(b, 2);
		isAskingForHelp = BooleanByteWrapper::GetFlag(b, 3);
	}
};

typedef boost::shared_ptr<FightOptionsInformations> FightOptionsInformationsPtr;

#endif