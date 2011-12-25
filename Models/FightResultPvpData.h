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

#ifndef __FIGHT_RESULT_PVP_DATA__
#define __FIGHT_RESULT_PVP_DATA__

class FightResultPvpData : public FightResultAdditionalData
{
public:
	uint8 grade;
	uint16 minHonorForGrade;
	uint16 maxHonorForGrade;
	uint16 honor;
	int16 honorDelta;
	uint16 dishonor;
	int16 dishonorDelta;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_PVP_DATA; }

	FightResultPvpData()
	{
	}

	FightResultPvpData(uint8 grade, uint16 minHonorForGrade, uint16 maxHonorForGrade, uint16 honor, int16 honorDelta, uint16 dishonor, int16 dishonorDelta) : grade(grade), minHonorForGrade(minHonorForGrade), maxHonorForGrade(maxHonorForGrade), honor(honor), honorDelta(honorDelta), dishonor(dishonor), dishonorDelta(dishonorDelta)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		FightResultAdditionalData::Serialize(data);
		data<<grade<<minHonorForGrade<<maxHonorForGrade<<honor<<honorDelta<<dishonor<<dishonorDelta;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightResultAdditionalData::Deserialize(data);
		data>>grade>>minHonorForGrade>>maxHonorForGrade>>honor>>honorDelta>>dishonor>>dishonorDelta;
	}
};

typedef boost::shared_ptr<FightResultPvpData> FightResultPvpDataPtr;

#endif