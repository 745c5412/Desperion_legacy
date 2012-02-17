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

#ifndef __SERVER_OPTIONAL_FEATURES_MESSAGE__
#define __SERVER_OPTIONAL_FEATURES_MESSAGE__

class ServerOptionalFeaturesMessage : public DofusMessage
{
public:
	std::vector<int16> features;

	virtual uint16 GetOpcode() const
	{ return SMSG_SERVER_OPTIONAL_FEATURES; }

	ServerOptionalFeaturesMessage()
	{
	}

	ServerOptionalFeaturesMessage(std::vector<int16>& features) : features(features)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = features.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<features[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		features.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 feature;
			data>>feature;
			features.push_back(feature);
		}
	}
};

#endif