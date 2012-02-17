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

#ifndef __FIGHT_RESULT_EXPERIENCE_DATA__
#define __FIGHT_RESULT_EXPERIENCE_DATA__

class FightResultExperienceData : public FightResultAdditionalData
{
public:
	bool showExperience;
	bool showExperienceLevelFloor;
	bool showExperienceNextLevelFloor;
	bool showExperienceFightDelta;
	bool showExperienceForGuild;
	bool showExperienceForMount;
	bool isIncarnationExperience;
	int64 experience;
	int64 experienceLevelFloor;
	int64 experienceNextLevelFloor;
	int experienceFightDelta;
	int experienceForGuild;
	int experienceForMount;

	uint16 GetProtocol() const
	{ return FIGHT_RESULT_EXPERIENCE_DATA; }

	FightResultExperienceData()
	{
	}

	FightResultExperienceData(bool showExperience, bool showExperienceLevelFloor, bool showExperienceNextLevelFloor, bool showExperienceFightDelta, bool showExperienceForGuild, bool showExperienceForMount, bool isIncarnationExperience, int64 experience, int64 experienceLevelFloor, int64 experienceNextLevelFloor, int experienceFightDelta, int experienceForGuild, int experienceForMount) : showExperience(showExperience), showExperienceLevelFloor(showExperienceLevelFloor), showExperienceNextLevelFloor(showExperienceNextLevelFloor), showExperienceFightDelta(showExperienceFightDelta), showExperienceForGuild(showExperienceForGuild), showExperienceForMount(showExperienceForMount), isIncarnationExperience(isIncarnationExperience), experience(experience), experienceLevelFloor(experienceLevelFloor), experienceNextLevelFloor(experienceNextLevelFloor), experienceFightDelta(experienceFightDelta), experienceForGuild(experienceForGuild), experienceForMount(experienceForMount)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FightResultAdditionalData::Serialize(data);
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, showExperience);
		BooleanByteWrapper::SetFlag(b, 1, showExperienceLevelFloor);
		BooleanByteWrapper::SetFlag(b, 2, showExperienceNextLevelFloor);
		BooleanByteWrapper::SetFlag(b, 3, showExperienceFightDelta);
		BooleanByteWrapper::SetFlag(b, 4, showExperienceForGuild);
		BooleanByteWrapper::SetFlag(b, 5, showExperienceForMount);
		BooleanByteWrapper::SetFlag(b, 6, isIncarnationExperience);
		data<<b<<experience<<experienceLevelFloor<<experienceNextLevelFloor<<experienceFightDelta<<experienceForGuild<<experienceForMount;
	}

	void Deserialize(ByteBuffer& data)
	{
		FightResultAdditionalData::Deserialize(data);
		int8 b;
		data>>b;
		showExperience = BooleanByteWrapper::GetFlag(b, 0);
		showExperienceLevelFloor = BooleanByteWrapper::GetFlag(b, 1);
		showExperienceNextLevelFloor = BooleanByteWrapper::GetFlag(b, 2);
		showExperienceFightDelta = BooleanByteWrapper::GetFlag(b, 3);
		showExperienceForGuild = BooleanByteWrapper::GetFlag(b, 4);
		showExperienceForMount = BooleanByteWrapper::GetFlag(b, 5);
		isIncarnationExperience = BooleanByteWrapper::GetFlag(b, 6);
		data>>experience>>experienceLevelFloor>>experienceNextLevelFloor>>experienceFightDelta>>experienceForGuild>>experienceForMount;
	}
};

typedef boost::shared_ptr<FightResultExperienceData> FightResultExperienceDataPtr;

#endif