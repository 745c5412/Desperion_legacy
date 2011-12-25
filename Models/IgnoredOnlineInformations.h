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

#ifndef __IGNORED_ONLINE_INFORMATIONS__
#define __IGNORED_ONLINE_INFORMATIONS__

class IgnoredOnlineInformations : public IgnoredInformations
{
public:
	std::string playerName;
	int8 breed;
	bool sex;

	uint16 GetProtocol() const
	{ return IGNORED_ONLINE_INFORMATIONS; }

	IgnoredOnlineInformations()
	{
	}

	IgnoredOnlineInformations(int accountId, std::string accountName, std::string playerName, int8 breed, bool sex) : IgnoredInformations(accountId, accountName), playerName(playerName), breed(breed), sex(sex)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		IgnoredInformations::Serialize(data);
		data<<playerName<<breed<<sex;
	}

	void Deserialize(ByteBuffer& data)
	{
		IgnoredInformations::Deserialize(data);
		data>>playerName>>breed>>sex;
	}
};

typedef boost::shared_ptr<IgnoredOnlineInformations> IgnoredOnlineInformationsPtr;

#endif