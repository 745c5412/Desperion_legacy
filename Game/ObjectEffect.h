#ifndef __OBJECT_EFFECT__
#define __OBJECT_EFFECT__

struct PlayerItemEffect;

class ObjectEffect : public DofusModel
{
public:
	virtual uint16 GetProtocol() const
	{ return OBJECT_EFFECT; }

	ObjectEffect(PlayerItemEffect*);
};

#endif