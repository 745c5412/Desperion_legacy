/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

    Desperion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Desperion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SET_UPDATE_MESSAGE__
#define __SET_UPDATE_MESSAGE__

class SetUpdateMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_SET_UPDATE; }

	SetUpdateMessage(int16 setId, std::vector<int16>& setObjects, const std::vector<EffectInstance*>& setEffects)
	{
		m_buffer<<setId;
		uint16 size = setObjects.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<setObjects[a];
		size = setEffects.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectEffectPtr e = setEffects[a]->ToPlayerItemEffect()->ToObjectEffect();
			m_buffer<<e->GetProtocol()<<*e;
		}
	}
};

#endif