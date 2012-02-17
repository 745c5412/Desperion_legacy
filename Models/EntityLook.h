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

#ifndef __ENTITY_LOOK__
#define __ENTITY_LOOK__

class EntityLook : public DofusModel
{
public:
	int16 bonesId;
	std::vector<int16> skins;
	std::vector<int> indexedColors;
	std::vector<int16> scales;
	std::vector<SubEntityPtr> subentities;

	virtual uint16 GetProtocol() const
	{ return ENTITY_LOOK; }

	EntityLook()
	{
	}

	EntityLook(const DEntityLook& look, std::vector<SubEntityPtr> subentities) : bonesId(look.bonesId), skins(look.skins), indexedColors(look.indexedColors),
		scales(look.scales), subentities(subentities)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<bonesId;
		uint16 size = skins.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<skins[a];
		size = indexedColors.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<indexedColors[a];
		size = scales.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<scales[a];
		size = subentities.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			subentities[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		skins.clear();
		indexedColors.clear();
		scales.clear();
		subentities.clear();
		data>>bonesId;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 skin;
			data>>skin;
			skins.push_back(skin);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int color;
			data>>color;
			indexedColors.push_back(color);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			SubEntityPtr sub(new SubEntity);
			sub->Deserialize(data);
			subentities.push_back(sub);
		}
	}
};

typedef boost::shared_ptr<EntityLook> EntityLookPtr;

#endif