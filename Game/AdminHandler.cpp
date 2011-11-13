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

#include "StdAfx.h"

Session::CommandStorageMap Session::m_commands;

void Session::InitCommandsTable()
{
	m_commands["man"].handler = &Session::HandleManCommand;
	m_commands["man"].level = 1;
	m_commands["man"].argc = 1;
	m_commands["man"].description = "Display informations about specified command";
	m_commands["man"].arguments = "[command]";

	m_commands["list"].handler = &Session::HandleListCommand;
	m_commands["list"].level = 1;
	m_commands["list"].argc = 0;
	m_commands["list"].description = "Display commands list";
	m_commands["list"].arguments = "";

	m_commands["moveto"].handler = &Session::HandleMoveToCommand;
	m_commands["moveto"].level = 3;
	m_commands["moveto"].argc = 1;
	m_commands["moveto"].description = "Move player to specified map";
	m_commands["moveto"].arguments = "[mapId] {cellId} {playername}";

	m_commands["additem"].handler = &Session::HandleAddItemCommand;
	m_commands["additem"].level = 3;
	m_commands["additem"].argc = 3;
	m_commands["additem"].description = "Create specified item";
	m_commands["additem"].arguments = "[id] [quantity] [max=true/false] {playername}";

	m_commands["nameannounce"].handler = &Session::HandleNameAnnounceCommand;
	m_commands["nameannounce"].level = 2;
	m_commands["nameannounce"].argc = 1;
	m_commands["nameannounce"].description = "Send specified admin message to the world";
	m_commands["nameannounce"].arguments = "[message]";
	
	m_commands["infomessage"].handler = &Session::HandleInfoMessageCommand;
	m_commands["infomessage"].level = 1;
	m_commands["infomessage"].argc = 2;
	m_commands["infomessage"].description = "(DEBUG) Send specified info message to client";
	m_commands["infomessage"].arguments = "[typeId] [messageId] {param 1} {param 2} ... {param n}";
}

void Session::HandleInfoMessageCommand(std::vector<std::string>& args, bool quiet)
{
	int8 type = atoi(args[0].c_str());
	int16 message = atoi(args[1].c_str());
	args.erase(args.begin(), args.begin() + 1);
	Send(TextInformationMessage(type, message, args));

	if(!quiet)
		Send(ConsoleMessage(CONSOLE_INFO_MESSAGE, "Message sent."));
}

void Session::HandleNameAnnounceCommand(std::vector<std::string>& args, bool quiet)
{
	std::string message = "";
	for(size_t a = 0; a < args.size(); ++a)
	{
		if(a != 0)
			message += " ";
		message += args[a];
	}

	// actuellement, deconnecte le client :x
	World::Instance().Send(ChatAdminServerMessage(0, message, time(NULL), ""));

	if(!quiet)
		Send(ConsoleMessage(CONSOLE_INFO_MESSAGE, "Message sent."));
}

void Session::HandleManCommand(std::vector<std::string>& args, bool quiet)
{
	Session::CommandStorageMap::iterator it = m_commands.find(args[0]);
	if(it == m_commands.end())
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, std::string("Command ") + args[0] + " doesn't exist."));
		return;
	}
	else if(it->second.level > m_data[FLAG_LEVEL].intValue)
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, std::string("Command ") + args[0] + " isn't accessible."));
		return;
	}

	std::ostringstream comm;
	comm<<"~ "<<it->first<<" ~\n";
	comm<<"Arguments: "<<it->second.arguments<<"\n";
	comm<<"Description: "<<it->second.description<<"\n";
	comm<<"Required level: "<<uint16(it->second.level)<<"\n";

	if(!quiet)
		Send(ConsoleMessage(CONSOLE_INFO_MESSAGE, comm.str()));
}

void Session::HandleListCommand(std::vector<std::string>& args, bool quiet)
{
	std::vector<std::string> aliases;
	std::vector<std::string> arguments;
	std::vector<std::string> descriptions;
	for(Session::CommandStorageMap::iterator it = m_commands.begin(); it != m_commands.end(); ++it)
	{
		if(it->second.level > m_data[FLAG_LEVEL].intValue)
			continue;
		aliases.push_back(it->first);
		arguments.push_back(it->second.arguments);
		descriptions.push_back(it->second.description);
	}

	Send(ConsoleCommandsListMessage(aliases, arguments, descriptions));
}

void Session::HandleMoveToCommand(std::vector<std::string>& args, bool quiet)
{
	int mapId = atoi(args[0].c_str());
	Map* map = World::Instance().GetMap(mapId);
	if(map == NULL)
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #1."));
		return;
	}

	int cellId = 399;
	if(args.size() > 1)
	{
		cellId = atoi(args[1].c_str());
		if(map->GetCell(cellId).id == -1)
		{
			if(!quiet)
				Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #2."));
			return;
		}
	}

	Character* ch = m_char;
	if(args.size() > 2)
	{
		CharacterMinimals* cm = World::Instance().GetCharacterMinimals(args[2]);
		if(cm == NULL || cm->onlineCharacter == NULL)
		{
			if(!quiet)
				Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #3."));
			return;
		}
		ch = cm->onlineCharacter;
	}

	ch->GetMap()->RemoveActor(ch->GetGuid());
	ch->SetMap(map);
	ch->SetCell(cellId);
	map->AddActor(ch);
	ch->GetSession()->Send(CurrentMapMessage(mapId));

	if(!quiet)
	{
		std::ostringstream comm;
		comm<<"Character "<<ch->GetName()<<" has been teleported to mapId "<<mapId<<", cellId "<<cellId<<".";
		Send(ConsoleMessage(CONSOLE_INFO_MESSAGE, comm.str()));
	}
}

void Session::HandleAddItemCommand(std::vector<std::string>& args, bool quiet)
{
	int id = atoi(args[0].c_str()), qua = atoi(args[1].c_str());
	std::string max = Desperion::ToLowerCase(args[2]);
	bool bmax;

	Item* item = World::Instance().GetItem(id);
	if(item == NULL)
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #1."));
		return;
	}
	else if(qua < 0 || qua > 10000)
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #2."));
		return;
	}

	if(max == "true")
		bmax = true;
	else if(max == "false")
		bmax = false;
	else
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #3."));
		return;
	}

	Character* ch = m_char;
	if(args.size() > 3)
	{
		CharacterMinimals* cm = World::Instance().GetCharacterMinimals(args[2]);
		if(cm == NULL || cm->onlineCharacter == NULL)
		{
			if(!quiet)
				Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Invalid argument #4."));
			return;
		}
		ch = cm->onlineCharacter;
	}

	PlayerItem* p = item->Create(qua, bmax, ch);
	PlayerItem::InsertIntoDB(p);
	ch->AddItem(p);
	ch->MoveItem(p, INVENTORY_POSITION_NOT_EQUIPED, true);

	if(!quiet)
	{
		std::ostringstream comm;
		comm<<"Character "<<ch->GetName()<<" got item ID "<<id<<", quantity "<<qua<<".";
		Send(ConsoleMessage(CONSOLE_INFO_MESSAGE, comm.str()));
	}
}

void Session::HandleAdminCommand(std::string& content, bool quiet)
{
	std::vector<std::string> table;
	Desperion::Split(table, content, ' ');
	if(table.empty())
		return;

	Session::CommandStorageMap::iterator it = m_commands.find(table[0]);
	if(it == m_commands.end())
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, std::string("Command ") + table[0] + " doesn't exist."));
		return;
	}
	CommandHandler *hdl = &it->second;
	if(hdl->level > m_data[FLAG_LEVEL].intValue)
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, std::string("Command ") + table[0] + " isn't accessible."));
		return;
	}
	table.erase(table.begin());
	if(hdl->argc > table.size())
	{
		if(!quiet)
			Send(ConsoleMessage(CONSOLE_ERR_MESSAGE, "Too few arguments in command call."));
		return;
	}
	(this->*hdl->handler)(table, quiet);
}

void Session::HandleAdminCommandMessage(ByteBuffer& packet)
{
	if(m_data[FLAG_LEVEL].intValue < 1)
		throw ServerError("Unauthorized access");
	AdminCommandMessage data;
	data.Deserialize(packet);
	HandleAdminCommand(data.content, false);
}

void Session::HandleAdminQuietCommandMessage(ByteBuffer& packet)
{
	if(m_data[FLAG_LEVEL].intValue < 1)
		throw ServerError("Unauthorized access");
	AdminQuietCommandMessage data;
	data.Deserialize(packet);
	HandleAdminCommand(data.content, true);
}