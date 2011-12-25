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

#ifndef __QUEST_ACTIVE_DETAILED_INFORMATIONS__
#define __QUEST_ACTIVE_DETAILED_INFORMATIONS__

class QuestActiveDetailedInformations : public QuestActiveInformations
{
public:
	int16 stepId;
	std::vector<QuestObjectiveInformationsPtr> objectives;

	uint16 GetProtocol() const
	{ return QUEST_ACTIVE_DETAILED_INFORMATIONS; }

	QuestActiveDetailedInformations()
	{
	}

	QuestActiveDetailedInformations(int16 questId, int16 stepId, std::vector<QuestObjectiveInformationsPtr>& objectives) : QuestActiveInformations(questId), stepId(stepId), objectives(objectives)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		QuestActiveInformations::Serialize(data);
		data<<stepId;
		uint16 size = objectives.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<objectives[a]->GetProtocol();
			objectives[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		QuestActiveInformations::Deserialize(data);
		data>>stepId;
		objectives.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			QuestObjectiveInformationsPtr model(Desperion::ProtocolTypeManager::GetQuestObjectiveInformations(protocol));
			model->Deserialize(data);
			objectives.push_back(model);
		}
	}
};

typedef boost::shared_ptr<QuestActiveDetailedInformations> QuestActiveDetailedInformationsPtr;

#endif