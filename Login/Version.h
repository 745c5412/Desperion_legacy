#ifndef __VERSION__
#define __VERSION__

class Version : public DofusModel
{
public:
	uint8 major, minor, release, patch, buildType;
	uint16 rev;

	uint32 GetProtocol() const
	{ return VERSION; }

	Version()
	{
	}

	void Init(ByteBuffer& data)
	{
		data>>major>>minor>>release>>rev>>patch>>buildType;
	}
};

#endif