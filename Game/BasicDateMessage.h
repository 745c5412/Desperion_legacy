#ifndef __BASIC_DATE_MESSAGE__
#define __BASIC_DATE_MESSAGE__

class BasicDateMessage : public DofusMessage
{
public:
	int8 day, month;
	int16 year;

	virtual uint16 GetOpcode() const
	{ return SMSG_BASIC_DATE; }

	BasicDateMessage()
	{
	}

	BasicDateMessage(int8 day, int8 month, int16 year) : day(day), month(month), year(year)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<day<<month<<year;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>day>>month>>year;
	}
};

#endif