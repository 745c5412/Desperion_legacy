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

#ifndef __ATLAS_POINTS_INFORMATIONS__
#define __ATLAS_POINTS_INFORMATIONS__

class AtlasPointsInformations : public DofusModel
{
public:
	int8 type;
	std::vector<MapCoordinatesExtendedPtr> coords;

	uint16 GetProtocol() const
	{ return ATLAS_POINTS_INFORMATIONS; }

	AtlasPointsInformations()
	{
	}

	AtlasPointsInformations(int8 type, std::vector<MapCoordinatesExtendedPtr>& coords) : type(type), coords(coords)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<type;
		uint16 size = coords.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			coords[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>type;
		coords.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MapCoordinatesExtendedPtr model(new MapCoordinatesExtended);
			model->Deserialize(data);
			coords.push_back(model);
		}
	}
};

typedef boost::shared_ptr<AtlasPointsInformations> AtlasPointsInformationsPtr;

#endif