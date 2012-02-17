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

#ifndef __ENABLED_CHANNELS_MESSAGE__
#define __ENABLED_CHANNELS_MESSAGE__

class EnabledChannelsMessage : public DofusMessage
{
public:
	std::set<int8> channels, disallowed;

	virtual uint16 GetOpcode() const
	{ return SMSG_ENABLED_CHANNELS; }

	EnabledChannelsMessage()
	{
	}

	EnabledChannelsMessage(std::set<int8>& channels, std::set<int8>& disallowed) : channels(channels),
		disallowed(disallowed)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = channels.size();
		data<<size;
		for(std::set<int8>::iterator it = channels.begin(); it != channels.end(); ++it)
			data<<*it;
		size = disallowed.size();
		data<<size;
		for(std::set<int8>::iterator it = disallowed.begin(); it != disallowed.end(); ++it)
			data<<*it;
	}

	void Deserialize(ByteBuffer& data)
	{
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 chann;
			data>>chann;
			channels.insert(chann);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 dis;
			data>>dis;
			disallowed.insert(dis);
		}
	}
};

#endif