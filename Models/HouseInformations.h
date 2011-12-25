#ifndef __HOUSE_INFORMATIONS__
#define __HOUSE_INFORMATIONS__

class HouseInformations : public DofusModel
{
public:
	bool isOnSale;
	bool isSaleLocked;
	int houseId;
	std::vector<int> doorsOnMap;
	std::string ownerName;
	int16 modelId;
	
	uint16 GetProtocol() const
	{ return HOUSE_INFORMATIONS; }
	
	HouseInformations()
	{
	}
	
	HouseInformations(bool isOnSale, bool isSaleLocked, int houseId, std::vector<int>& doorsOnMap, std::string ownerName,
		int16 modelId) : isOnSale(isOnSale), isSaleLocked(isSaleLocked), houseId(houseId), doorsOnMap(doorsOnMap),
		ownerName(ownerName), modelId(modelId)
	{
	}
	
	void Serialize(ByteBuffer& data)
	{
		int8 b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, isOnSale);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, isSaleLocked);
		data<<b<<houseId;
		uint16 size = doorsOnMap.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<doorsOnMap[a];
		data<<ownerName<<modelId;
	}
	
	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		isOnSale = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		isSaleLocked = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		data>>houseId;
		doorsOnMap.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			doorsOnMap.push_back(val);
		}
		data>>ownerName>>modelId;
	}
};

typedef boost::shared_ptr<HouseInformations> HouseInformationsPtr;

#endif