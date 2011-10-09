#ifndef __DOFUS_MODEL__
#define __DOFUS_MODEL__

class DofusModel
{
protected:
	ByteBuffer m_buffer;
public:
	virtual uint32 GetProtocol() const = 0;

	operator ByteBuffer() const
	{ return m_buffer; }
	
	DofusModel()
	{
	}
};

#endif