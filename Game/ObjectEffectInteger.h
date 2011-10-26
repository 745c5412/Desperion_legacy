#ifndef __OBJECT_EFFECT_INTEGER__
#define __OBJECT_EFFECT_INTEGER__

struct PlayerItemEffectInteger;

class ObjectEffectInteger : public ObjectEffect
{
public:
	virtual uint16 GetProtocol() const
	{ return OBJECT_EFFECT_INTEGER; }

	ObjectEffectInteger(PlayerItemEffectInteger*);
};

#endif