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

#ifndef __ACHIEVEMENT_STARTED_VALUE__
#define __ACHIEVEMENT_STARTED_VALUE__

class AchievementStartedValue : public Achievement
{
public:
	int16 value;
	int16 maxValue;

	uint16 GetProtocol() const
	{ return ACHIEVEMENT_STARTED_VALUE; }

	AchievementStartedValue()
	{
	}

	AchievementStartedValue(int16 achievementId, int16 value, int16 maxValue) : Achievement(achievementId), value(value), maxValue(maxValue)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		Achievement::Serialize(data);
		data<<value<<maxValue;
	}

	void Deserialize(ByteBuffer& data)
	{
		Achievement::Deserialize(data);
		data>>value>>maxValue;
	}
};

typedef boost::shared_ptr<AchievementStartedValue> AchievementStartedValuePtr;

#endif