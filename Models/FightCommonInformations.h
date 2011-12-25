#ifndef __FIGHT_COMMON_INFORMATIONS__
#define __FIGHT_COMMON_INFORMATIONS__

class FightCommonInformations : public DofusModel
{
public:
	int fightId;
	int8 fightType;
	std::vector<FightTeamInformationsPtr> fightTeams;
	std::vector<int16> fightTeamsPositions;
	std::vector<FightOptionsInformationsPtr> fightTeamsOptions;
	
	uint16 GetProtocol() const
	{ return FIGHT_COMMON_INFORMATIONS; }
	
	FightCommonInformations()
	{
	}
	
	FightCommonInformations(int fightId, int8 fightType, std::vector<FightTeamInformationsPtr>& fightTeams,
		std::vector<int16>& fightTeamsPositions, std::vector<FightOptionsInformationsPtr>& fightTeamsOptions)
		: fightId(fightId), fightType(fightType), fightTeams(fightTeams), fightTeamsPositions(fightTeamsPositions),
		fightTeamsOptions(fightTeamsOptions)
	{
	}
	
	void Serialize(ByteBuffer& data)
	{
		data<<fightId<<fightType;
		uint16 size = fightTeams.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<fightTeams[a]->GetProtocol();
			fightTeams[a]->Serialize(data);
		}
		size = fightTeamsPositions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<fightTeamsPositions[a];
		size = fightTeamsOptions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			fightTeamsOptions[a]->Serialize(data);
	}
	
	void Deserialize(ByteBuffer& data)
	{
		data>>fightId>>fightType;
		fightTeams.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FightTeamInformationsPtr model(Desperion::ProtocolTypeManager::GetFightTeamInformations(protocol));
			model->Deserialize(data);
			fightTeams.push_back(model);
		}
		fightTeamsPositions.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 pos;
			data>>pos;
			fightTeamsPositions.push_back(pos);
		}
		fightTeamsOptions.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			FightOptionsInformationsPtr model(new FightOptionsInformations);
			model->Deserialize(data);
			fightTeamsOptions.push_back(model);
		}
	}
};

typedef boost::shared_ptr<FightCommonInformations> FightCommonInformationsPtr;

#endif