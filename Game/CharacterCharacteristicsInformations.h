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

#ifndef __CHARACTER_CHARACTERISTICS_INFORMATIONS__
#define __CHARACTER_CHARACTERISTICS_INFORMATIONS__

class CharacterCharacteristicsInformations : public DofusModel
{
public:
	ByteBuffer m_buffer; // en attendant ^^

	virtual uint16 GetProtocol() const
	{ return CHARACTER_CHARACTERISTICS_INFORMATIONS; }

	CharacterCharacteristicsInformations()
	{
	}

	CharacterCharacteristicsInformations(Character*);

	void Serialize(ByteBuffer& data) // idem :)
	{
		size_t size = m_buffer.Size();
		if(size > 0)
			data.AppendBytes(m_buffer.Contents(), size);
	}

	void Deserialize(ByteBuffer& data)
	{
	}
};

typedef boost::shared_ptr<CharacterCharacteristicsInformations> CharacterCharacteristicsInformationsPtr;

#endif