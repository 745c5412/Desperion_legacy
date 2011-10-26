#ifndef __OBJECT_EFFECT_DICE__
#define __OBJECT_EFFECT_DICE__

struct PlayerItemEffectDice;

class ObjectEffectDice : public ObjectEffect
{
public:
	virtual uint16 GetProtocol() const
	{ return OBJECT_EFFECT_DICE; }

	ObjectEffectDice(PlayerItemEffectDice*);
};

#endif