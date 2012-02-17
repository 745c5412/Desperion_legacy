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

#ifndef __JOB_EXPERIENCE__
#define __JOB_EXPERIENCE__

class JobExperience : public DofusModel
{
public:
	int8 jobId;
	int8 jobLevel;
	int64 jobXP;
	int64 jobXpLevelFloor;
	int64 jobXpNextLevelFloor;

	uint16 GetProtocol() const
	{ return JOB_EXPERIENCE; }

	JobExperience()
	{
	}

	JobExperience(int8 jobId, int8 jobLevel, int64 jobXP, int64 jobXpLevelFloor, int64 jobXpNextLevelFloor) : jobId(jobId), jobLevel(jobLevel), jobXP(jobXP), jobXpLevelFloor(jobXpLevelFloor), jobXpNextLevelFloor(jobXpNextLevelFloor)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<jobId<<jobLevel<<jobXP<<jobXpLevelFloor<<jobXpNextLevelFloor;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>jobId>>jobLevel>>jobXP>>jobXpLevelFloor>>jobXpNextLevelFloor;
	}
};

typedef boost::shared_ptr<JobExperience> JobExperiencePtr;

#endif