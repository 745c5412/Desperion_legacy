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

#ifndef __INTERACTIVE_MAP_UPDATE_MESSAGE__
#define __INTERACTIVE_MAP_UPDATE_MESSAGE__

class InteractiveMapUpdateMessage : public DofusMessage
{
public:
	std::vector<InteractiveElementPtr> interactiveElements;

	uint16 GetOpcode() const
	{ return SMSG_INTERACTIVE_MAP_UPDATE; }

	InteractiveMapUpdateMessage()
	{
	}

	InteractiveMapUpdateMessage(std::vector<InteractiveElementPtr>& interactiveElements) : interactiveElements(interactiveElements)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = interactiveElements.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			interactiveElements[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		interactiveElements.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			InteractiveElementPtr model(new InteractiveElement);
			model->Deserialize(data);
			interactiveElements.push_back(model);
		}
	}
};

#endif