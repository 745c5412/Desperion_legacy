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

#ifndef __HUMAN_INFORMATIONS__
#define __HUMAN_INFORMATIONS__

class HumanInformations : public DofusModel
{
public:
	std::vector<EntityLookPtr> followingCharactersLook;
	int8 emoteId;
	int64 emoteStartTime;
	ActorRestrictionsInformationsPtr restrictions;
	int16 titleId;
	std::string titleParam;

	uint16 GetProtocol() const
	{ return HUMAN_INFORMATIONS; }

	HumanInformations()
	{
	}

	HumanInformations(const std::vector<EntityLookPtr>& followingCharactersLook, int8 emoteId, int64 emoteStartTime, ActorRestrictionsInformations* restrictions, int16 titleId, std::string titleParam) : followingCharactersLook(followingCharactersLook), emoteId(emoteId), emoteStartTime(emoteStartTime), restrictions(restrictions), titleId(titleId), titleParam(titleParam)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = followingCharactersLook.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			followingCharactersLook[a]->Serialize(data);
		data<<emoteId<<emoteStartTime;
		restrictions->Serialize(data);
		data<<titleId<<titleParam;
	}

	void Deserialize(ByteBuffer& data)
	{
		followingCharactersLook.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			EntityLookPtr model(new EntityLook);
			model->Deserialize(data);
			followingCharactersLook.push_back(model);
		}
		data>>emoteId>>emoteStartTime;
		restrictions.reset(new ActorRestrictionsInformations);
		restrictions->Deserialize(data);
		data>>titleId>>titleParam;
	}
};

typedef boost::shared_ptr<HumanInformations> HumanInformationsPtr;

#endif