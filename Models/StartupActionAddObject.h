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

#ifndef __STARTUP_ACTION_ADD_OBJECT__
#define __STARTUP_ACTION_ADD_OBJECT__

class StartupActionAddObject : public DofusModel
{
public:
	int uid;
	std::string title;
	std::string text;
	std::string descUrl;
	std::string pictureUrl;
	std::vector<ObjectItemMinimalInformationPtr> items;

	uint16 GetProtocol() const
	{ return STARTUP_ACTION_ADD_OBJECT; }

	StartupActionAddObject()
	{
	}

	StartupActionAddObject(int uid, std::string title, std::string text, std::string descUrl, std::string pictureUrl, std::vector<ObjectItemMinimalInformationPtr>& items) : uid(uid), title(title), text(text), descUrl(descUrl), pictureUrl(pictureUrl), items(items)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<uid<<title<<text<<descUrl<<pictureUrl;
		uint16 size = items.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			items[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>uid>>title>>text>>descUrl>>pictureUrl;
		items.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemMinimalInformationPtr model(new ObjectItemMinimalInformation);
			model->Deserialize(data);
			items.push_back(model);
		}
	}
};

typedef boost::shared_ptr<StartupActionAddObject> StartupActionAddObjectPtr;

#endif