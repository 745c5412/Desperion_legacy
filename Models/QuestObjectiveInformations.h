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

#ifndef __QUEST_OBJECTIVE_INFORMATIONS__
#define __QUEST_OBJECTIVE_INFORMATIONS__

class QuestObjectiveInformations : public DofusModel
{
public:
	int16 objectiveId;
	bool objectiveStatus;

	uint16 GetProtocol() const
	{ return QUEST_OBJECTIVE_INFORMATIONS; }

	QuestObjectiveInformations()
	{
	}

	QuestObjectiveInformations(int16 objectiveId, bool objectiveStatus) : objectiveId(objectiveId), objectiveStatus(objectiveStatus)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<objectiveId<<objectiveStatus;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>objectiveId>>objectiveStatus;
	}
};

typedef boost::shared_ptr<QuestObjectiveInformations> QuestObjectiveInformationsPtr;

#endif