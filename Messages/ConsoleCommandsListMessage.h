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

#ifndef __CONSOLE_COMMANDS_LIST_MESSAGE__
#define __CONSOLE_COMMANDS_LIST_MESSAGE__

class ConsoleCommandsListMessage : public DofusMessage
{
public:
	std::vector<std::string> aliases;
	std::vector<std::string> arguments;
	std::vector<std::string> descriptions;

	uint16 GetOpcode() const
	{ return SMSG_CONSOLE_COMMANDS_LIST; }

	ConsoleCommandsListMessage()
	{
	}

	ConsoleCommandsListMessage(std::vector<std::string>& aliases, std::vector<std::string>& arguments, std::vector<std::string>& descriptions) : aliases(aliases), arguments(arguments), descriptions(descriptions)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = aliases.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<aliases[a];
		size = arguments.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<arguments[a];
		size = descriptions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<descriptions[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		aliases.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string val;
			data>>val;
			aliases.push_back(val);
		}
		arguments.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string val;
			data>>val;
			arguments.push_back(val);
		}
		descriptions.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string val;
			data>>val;
			descriptions.push_back(val);
		}
	}
};

#endif