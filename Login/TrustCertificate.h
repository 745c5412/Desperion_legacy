#ifndef __TRUST_CERTIFICATE__
#define __TRUST_CERTIFICATE__

class TrustCertificate : public DofusModel
{
public:
	int id;
	std::string hash;

	virtual uint16 GetProtocol() const
	{ return TRUST_CERTIFICATE; }

	TrustCertificate()
	{
	}

	TrustCertificate(int id, std::string hash) : id(id), hash(hash)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<id<<hash;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>id>>hash;
	}
};

typedef boost::shared_ptr<TrustCertificate> TrustCertificatePtr;

#endif