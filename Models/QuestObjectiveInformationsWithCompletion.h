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

#ifndef __QUEST_OBJECTIVE_INFORMATIONS_WITH_COMPLETION__
#define __QUEST_OBJECTIVE_INFORMATIONS_WITH_COMPLETION__

class QuestObjectiveInformationsWithCompletion : public QuestObjectiveInformations
{
public:
	int16 curCompletion;
	int16 maxCompletion;

	uint16 GetProtocol() const
	{ return QUEST_OBJECTIVE_INFORMATIONS_WITH_COMPLETION; }

	QuestObjectiveInformationsWithCompletion()
	{
	}

	QuestObjectiveInformationsWithCompletion(int16 objectiveId, bool objectiveStatus, int16 curCompletion, int16 maxCompletion) : QuestObjectiveInformations(objectiveId, objectiveStatus), curCompletion(curCompletion), maxCompletion(maxCompletion)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		QuestObjectiveInformations::Serialize(data);
		data<<curCompletion<<maxCompletion;
	}

	void Deserialize(ByteBuffer& data)
	{
		QuestObjectiveInformations::Deserialize(data);
		data>>curCompletion>>maxCompletion;
	}
};

typedef boost::shared_ptr<QuestObjectiveInformationsWithCompletion> QuestObjectiveInformationsWithCompletionPtr;

#endif