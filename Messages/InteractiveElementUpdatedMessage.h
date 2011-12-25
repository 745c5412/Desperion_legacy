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

#ifndef __INTERACTIVE_ELEMENT_UPDATED_MESSAGE__
#define __INTERACTIVE_ELEMENT_UPDATED_MESSAGE__

class InteractiveElementUpdatedMessage : public DofusMessage
{
public:
	InteractiveElementPtr interactiveElement;

	uint16 GetOpcode() const
	{ return SMSG_INTERACTIVE_ELEMENT_UPDATED; }

	InteractiveElementUpdatedMessage()
	{
	}

	InteractiveElementUpdatedMessage(InteractiveElement* interactiveElement) : interactiveElement(interactiveElement)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		interactiveElement->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		interactiveElement.reset(new InteractiveElement);
		interactiveElement->Deserialize(data);
	}
};

#endif