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

#ifndef __GAME_SERVER_INFORMATIONS__
#define __GAME_SERVER_INFORMATIONS__

class GameServerInformations : public DofusModel
{
public:
	int16 id;
	int8 status, completion, charactersCount;
	bool isSelectable;
	uint64 date;

	virtual uint16 GetProtocol() const
	{ return GAME_SERVER_INFORMATIONS; }

	GameServerInformations()
	{
	}

	GameServerInformations(int16 id, int8 status, int8 completion, bool isSelectable, int8 charactersCount, uint64 date) : id(id),
		status(status), completion(completion), isSelectable(isSelectable), charactersCount(charactersCount), date(date)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<id<<status<<completion<<isSelectable<<charactersCount<<date;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>id>>status>>completion>>isSelectable>>charactersCount>>date;
	}
};

typedef boost::shared_ptr<GameServerInformations> GameServerInformationsPtr;

#endif