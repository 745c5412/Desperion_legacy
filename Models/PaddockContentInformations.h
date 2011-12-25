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

#ifndef __PADDOCK_CONTENT_INFORMATIONS__
#define __PADDOCK_CONTENT_INFORMATIONS__

class PaddockContentInformations : public PaddockInformations
{
public:
	int paddockId;
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;
	bool abandonned;
	std::vector<MountInformationsForPaddockPtr> mountsInformations;

	uint16 GetProtocol() const
	{ return PADDOCK_CONTENT_INFORMATIONS; }

	PaddockContentInformations()
	{
	}

	PaddockContentInformations(int16 maxOutdoorMount, int16 maxItems, int paddockId, int16 worldX, int16 worldY, int mapId, int16 subAreaId, bool abandonned, std::vector<MountInformationsForPaddockPtr>& mountsInformations) : PaddockInformations(maxOutdoorMount, maxItems), paddockId(paddockId), worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId), abandonned(abandonned), mountsInformations(mountsInformations)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		PaddockInformations::Serialize(data);
		data<<paddockId<<worldX<<worldY<<mapId<<subAreaId<<abandonned;
		uint16 size = mountsInformations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			mountsInformations[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		PaddockInformations::Deserialize(data);
		data>>paddockId>>worldX>>worldY>>mapId>>subAreaId>>abandonned;
		mountsInformations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MountInformationsForPaddockPtr model(new MountInformationsForPaddock);
			model->Deserialize(data);
			mountsInformations.push_back(model);
		}
	}
};

typedef boost::shared_ptr<PaddockContentInformations> PaddockContentInformationsPtr;

#endif