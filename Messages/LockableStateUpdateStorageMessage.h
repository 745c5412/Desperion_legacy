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

#ifndef __LOCKABLE_STATE_UPDATE_STORAGE_MESSAGE__
#define __LOCKABLE_STATE_UPDATE_STORAGE_MESSAGE__

class LockableStateUpdateStorageMessage : public LockableStateUpdateAbstractMessage
{
public:
	int mapId;
	int elementId;

	uint16 GetOpcode() const
	{ return SMSG_LOCKABLE_STATE_UPDATE_STORAGE; }

	LockableStateUpdateStorageMessage()
	{
	}

	LockableStateUpdateStorageMessage(bool locked, int mapId, int elementId) : LockableStateUpdateAbstractMessage(locked), mapId(mapId), elementId(elementId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		LockableStateUpdateAbstractMessage::Serialize(data);
		data<<mapId<<elementId;
	}

	void Deserialize(ByteBuffer& data)
	{
		LockableStateUpdateAbstractMessage::Deserialize(data);
		data>>mapId>>elementId;
	}
};

#endif