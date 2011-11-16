#ifndef __SUB_ENTITY__
#define __SUB_ENTITY__

class EntityLook;

class SubEntity : public DofusModel
{
public:
	int8 bindingPointCategory;
	int8 bindingPointIndex;
	EntityLook* look;

	virtual uint16 GetProtocol() const
	{ return SUB_ENTITY; }

	SubEntity()
	{
	}

	SubEntity(int8 bindingPointCategory, int8 bindingPointIndex, EntityLook* look);

	void Serialize(ByteBuffer& data);

	void Deserialize(ByteBuffer& data);

	~SubEntity();
};

typedef boost::shared_ptr<SubEntity> SubEntityPtr;

#endif