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

#ifndef __IGNORED_LIST_MESSAGE__
#define __IGNORED_LIST_MESSAGE__

class IgnoredListMessage : public DofusMessage
{
public:
	std::vector<IgnoredInformationsPtr> ignoredList;

	uint16 GetOpcode() const
	{ return SMSG_IGNORED_LIST; }

	IgnoredListMessage()
	{
	}

	IgnoredListMessage(std::vector<IgnoredInformationsPtr>& ignoredList) : ignoredList(ignoredList)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = ignoredList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<ignoredList[a]->GetProtocol();
			ignoredList[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		ignoredList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			IgnoredInformationsPtr model(Desperion::ProtocolTypeManager::GetIgnoredInformations(protocol));
			model->Deserialize(data);
			ignoredList.push_back(model);
		}
	}
};

#endif