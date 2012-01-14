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

template<> Session::HandlerStorageMap AbstractSession<GamePacketHandler>::m_handlers;

void Session::RemoveChannel(int8 chann)
{
	std::set<int8>::iterator it = m_channels.find(chann);
	if(it != m_channels.end())
		m_channels.erase(it);
}

FriendOnlineInformations* Session::GetFriendInformations(bool isFriend)
{
	return new FriendOnlineInformations(m_data[FLAG_GUID].intValue, m_data[FLAG_PSEUDO].stringValue,
			isFriend ? m_char->GetContextType() : 0, 0, m_char->GetName(),
			isFriend ? m_char->GetLevel() : 0,m_char->GetStats().GetAlignmentSide(), m_char->GetBreed(),
			m_char->GetSex(), isFriend ? new BasicGuildInformations(0, "vraies infos de guilde") : new BasicGuildInformations(0, ""),
				m_char->GetSmileyId());
}

IgnoredOnlineInformations* Session::GetIgnoredInformations()
{
	return new IgnoredOnlineInformations(m_data[FLAG_GUID].intValue, m_data[FLAG_PSEUDO].stringValue, m_char->GetName(),
		m_char->GetBreed(), m_char->GetSex());
}

void Session::SendCharacterStatsListMessage()
{
	CharacterStats& s = m_char->GetStats();
	Send(CharacterStatsListMessage(new CharacterCharacteristicsInformations(s.GetXp(), 0, 0, s.GetKamas(), s.GetStatsPoints(),
		s.GetSpellsPoints(), new ActorExtendedAlignmentInformations(s.GetAlignmentSide(), s.GetAlignmentValue(),
		s.GetAlignmentGrade(), s.GetDishonor(), m_char->GetLevel(), s.GetHonor(), 0, 0, s.IsPvpEnabled()),
		m_char->GetCurrentLife(), m_char->GetMaxLife(), s.GetEnergy(), 10000, s.GetCurrentAp(), s.GetCurrentMp(),
		s.initiative.ToBase(), s.prospecting.ToBase(), s.actionPoints.ToBase(), s.movementPoints.ToBase(), s.strength.ToBase(),
		s.vitality.ToBase(), s.wisdom.ToBase(), s.chance.ToBase(), s.agility.ToBase(), s.intelligence.ToBase(), s.range.ToBase(),
		s.summonableCreaturesBoost.ToBase(), s.reflect.ToBase(), s.criticalHit.ToBase(), 50, s.criticalMiss.ToBase(),
		s.healBonus.ToBase(), s.allDamagesBonus.ToBase(), s.weaponDamagesBonusPercent.ToBase(), s.damagesBonusPercent.ToBase(),
		s.trapBonus.ToBase(), s.trapBonusPercent.ToBase(), s.permanentDamagePercent.ToBase(), s.tackleBlock.ToBase(),
		s.tackleEvade.ToBase(), s.PAAttack.ToBase(), s.PMAttack.ToBase(), s.pushDamageBonus.ToBase(), s.criticalDamageBonus.ToBase(),
		s.neutralDamageBonus.ToBase(), s.earthDamageBonus.ToBase(), s.waterDamageBonus.ToBase(), s.airDamageBonus.ToBase(),
		s.fireDamageBonus.ToBase(), s.dodgePALostProbability.ToBase(), s.dodgePMLostProbability.ToBase(),
		s.neutralElementResistPercent.ToBase(), s.earthElementResistPercent.ToBase(), s.waterElementResistPercent.ToBase(),
		s.airElementResistPercent.ToBase(), s.fireElementResistPercent.ToBase(), s.neutralElementReduction.ToBase(),
		s.earthElementReduction.ToBase(), s.waterElementReduction.ToBase(), s.airElementReduction.ToBase(),
		s.fireElementReduction.ToBase(), s.pushDamageReduction.ToBase(), s.criticalDamageReduction.ToBase(),
		s.pvpNeutralElementResistPercent.ToBase(), s.pvpEarthElementResistPercent.ToBase(), s.pvpWaterElementResistPercent.ToBase(),
		s.pvpAirElementResistPercent.ToBase(), s.pvpFireElementResistPercent.ToBase(), s.pvpNeutralElementReduction.ToBase(),
		s.pvpEarthElementReduction.ToBase(), s.pvpWaterElementReduction.ToBase(), s.pvpAirElementReduction.ToBase(),
		s.pvpFireElementReduction.ToBase(), std::vector<CharacterSpellModificationPtr>())));
}

void Session::LOG(const char* str, ...)
{
	if(m_data[FLAG_GUID].intValue == 0 || !str)
		return;

	if(!m_logs)
	{
		std::ostringstream fileName;
		fileName<<"sessions/"<<m_data[FLAG_GUID].intValue<<".log";
		m_logs.open(fileName.str().c_str(), std::ios::app);
	}

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

	Log::Instance().outFile(m_logs, std::string(buf));
}

void Session::InitHandlersTable()
{
	m_handlers[CMSG_AUTHENTICATION_TICKET].Handler = &Session::HandleAuthenticationTicketMessage;
	m_handlers[CMSG_AUTHENTICATION_TICKET].Flag = FLAG_NOT_CONNECTED;
	m_handlers[CMSG_ADMIN_COMMAND].Handler = &Session::HandleAdminCommandMessage;
	m_handlers[CMSG_ADMIN_QUIET_COMMAND].Handler = &Session::HandleAdminQuietCommandMessage;

	m_handlers[CMSG_CHARACTERS_LIST_REQUEST].Handler = &Session::HandleCharactersListRequestMessage;
	m_handlers[CMSG_CHARACTERS_LIST_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_DELETION_REQUEST].Handler = &Session::HandleCharacterDeletionRequestMessage;
	m_handlers[CMSG_CHARACTER_DELETION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_NAME_SUGGESTION_REQUEST].Handler = &Session::HandleCharacterNameSuggestionRequestMessage;
	m_handlers[CMSG_CHARACTER_NAME_SUGGESTION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_SELECTION].Handler = &Session::HandleCharacterSelectionMessage;
	m_handlers[CMSG_CHARACTER_SELECTION].Flag = FLAG_OUT_OF_QUEUE;
	m_handlers[CMSG_CHARACTER_CREATION_REQUEST].Handler = &Session::HandleCharacterCreationRequestMessage;
	m_handlers[CMSG_CHARACTER_CREATION_REQUEST].Flag = FLAG_OUT_OF_QUEUE;

	m_handlers[CMSG_GAME_CONTEXT_CREATE_REQUEST].Handler = &Session::HandleGameContextCreateRequestMessage;
	m_handlers[CMSG_MAP_INFORMATIONS_REQUEST].Handler = &Session::HandleMapInformationsRequestMessage;
	m_handlers[CMSG_GAME_MAP_MOVEMENT_REQUEST].Handler = &Session::HandleGameMapMovementRequestMessage;
	m_handlers[CMSG_GAME_MAP_MOVEMENT_CONFIRM].Handler = &Session::HandleGameMapMovementConfirmMessage;
	m_handlers[CMSG_CHANGE_MAP].Handler = &Session::HandleChangeMapMessage;
	
	m_handlers[CMSG_CHAT_CLIENT_MULTI].Handler = &Session::HandleChatClientMultiMessage;
	m_handlers[CMSG_CHAT_CLIENT_MULTI_WITH_OBJECT].Handler = &Session::HandleChatClientMultiWithObjectMessage;
	m_handlers[CMSG_CHAT_CLIENT_PRIVATE].Handler = &Session::HandleChatClientPrivateMessage;
	m_handlers[CMSG_CHAT_CLIENT_PRIVATE_WITH_OBJECT].Handler = &Session::HandleChatClientPrivateWithObjectMessage;
	m_handlers[CMSG_CHANNEL_ENABLING].Handler = &Session::HandleChannelEnablingMessage;
	m_handlers[CMSG_CHAT_SMILEY_REQUEST].Handler = &Session::HandleChatSmileyRequestMessage;
	m_handlers[CMSG_MOOD_SMILEY_REQUEST].Handler = &Session::HandleMoodSmileyRequestMessage;

	m_handlers[CMSG_OBJECT_DROP].Handler = &Session::HandleObjectDropMessage;
	m_handlers[CMSG_OBJECT_DELETE].Handler = &Session::HandleObjectDeleteMessage;
	m_handlers[CMSG_OBJECT_SET_POSITION].Handler = &Session::HandleObjectSetPositionMessage;
	m_handlers[CMSG_LIVING_OBJECT_CHANGE_SKIN_REQUEST].Handler = &Session::HandleLivingObjectChangeSkinRequestMessage;
	m_handlers[CMSG_LIVING_OBJECT_DISSOCIATE].Handler = &Session::HandleLivingObjectDissociateMessage;
	m_handlers[CMSG_LIVING_OBJECT_MESSAGE_REQUEST].Handler = &Session::HandleLivingObjectMessageRequestMessage;
	m_handlers[CMSG_OBJECT_FEED].Handler = &Session::HandleObjectFeedMessage;
	
	m_handlers[CMSG_BASIC_PING].Handler = &Session::HandleBasicPingMessage;
	m_handlers[CMSG_BASIC_WHO_AM_I_REQUEST].Handler = &Session::HandleBasicWhoAmIRequestMessage;
	m_handlers[CMSG_BASIC_WHO_IS_REQUEST].Handler = &Session::HandleBasicWhoIsRequestMessage;
	m_handlers[CMSG_NUMERIC_WHO_IS_REQUEST].Handler = &Session::HandleNumericWhoIsRequestMessage;

	m_handlers[CMSG_FRIENDS_GET_LIST].Handler = &Session::HandleFriendsGetListMessage;
	m_handlers[CMSG_IGNORED_GET_LIST].Handler = &Session::HandleIgnoredGetListMessage;
	m_handlers[CMSG_IGNORED_DELETE_REQUEST].Handler = &Session::HandleIgnoredDeleteRequestMessage;
	m_handlers[CMSG_IGNORED_ADD_REQUEST].Handler = &Session::HandleIgnoredAddRequestMessage;
	m_handlers[CMSG_FRIEND_SET_WARN_ON_CONNECTION].Handler = &Session::HandleFriendSetWarnOnConnectionMessage;
	m_handlers[CMSG_FRIEND_SET_WARN_ON_LEVEL_GAIN].Handler = &Session::HandleFriendSetWarnOnLevelGainMessage;
	m_handlers[CMSG_GUILD_MEMBER_SET_WARN_ON_CONNECTION].Handler = &Session::HandleGuildMemberSetWarnOnConnectionMessage;
	m_handlers[CMSG_FRIEND_ADD_REQUEST].Handler = &Session::HandleFriendAddRequestMessage;
	m_handlers[CMSG_FRIEND_DELETE_REQUEST].Handler = &Session::HandleFriendDeleteRequestMessage;

	m_handlers[CMSG_PARTY_INVITATION_REQUEST].Handler = &Session::HandlePartyInvitationRequestMessage;
	m_handlers[CMSG_PARTY_REFUSE_INVITATION].Handler = &Session::HandlePartyRefuseInvitationMessage;
	m_handlers[CMSG_PARTY_ACCEPT_INVITATION].Handler = &Session::HandlePartyAcceptInvitationMessage;
	m_handlers[CMSG_PARTY_KICK_REQUEST].Handler = &Session::HandlePartyKickRequestMessage;
	m_handlers[CMSG_PARTY_INVITATION_DETAILS_REQUEST].Handler = &Session::HandlePartyInvitationDetailsRequestMessage;
	m_handlers[CMSG_PARTY_LEAVE_REQUEST].Handler = &Session::HandlePartyLeaveRequestMessage;
	m_handlers[CMSG_PARTY_ABDICATE_THRONE].Handler = &Session::HandlePartyAbdicateThroneMessage;
	m_handlers[CMSG_PARTY_CANCEL_INVITATION].Handler = &Session::HandlePartyCancelInvitationMessage;
}

void Session::HandleAuthenticationTicketMessage(ByteBuffer& packet)
{
	AuthenticationTicketMessage data;
	data.Deserialize(packet);

	const char* query = "SELECT guid, answer, pseudo, level, lastIP, lastConnectionDate, subscriptionEnd, channels, disallowed FROM accounts \
						WHERE ticket='%s' LIMIT 1;";
	ResultPtr QR = Desperion::eDatabase.Query(query, data.ticket.c_str());
	if(QR)
	{
		Field* fields = QR->Fetch();
		m_data[FLAG_GUID].intValue = fields[0].GetUInt32();
		m_data[FLAG_PSEUDO].stringValue = fields[2].GetString();
		m_data[FLAG_LEVEL].intValue = fields[3].GetUInt8();
		m_data[FLAG_ANSWER].stringValue = fields[1].GetString();
		m_data[FLAG_LAST_CONN].intValue = fields[4].GetUInt32();
		m_data[FLAG_LAST_IP].stringValue = fields[5].GetString();
		m_subscriptionEnd = fields[6].GetUInt32();
		Desperion::FastSplitSet<','>(m_channels, std::string(fields[7].GetString()), Desperion::SplitInt);
		Desperion::FastSplitSet<','>(m_disallowed, std::string(fields[8].GetString()), Desperion::SplitInt);
	}
	else
	{
		Send(AuthenticationTicketRefusedMessage());
		m_socket->close();
		return;
	}

	QR = Desperion::eDatabase.Query("SELECT * FROM account_social WHERE guid=%u LIMIT 1;", m_data[FLAG_GUID].intValue);
	if(QR)
	{
		Field* fields = QR->Fetch();
		std::vector<std::string> friends, ennemies;
		Desperion::FastSplitString<';'>(friends, std::string(fields[1].GetString()), true);
		Desperion::FastSplitString<';'>(ennemies, std::string(fields[2].GetString()), true);
		for(size_t a = 0; a < friends.size(); ++a)
		{
			std::vector<std::string> intern;
			Desperion::FastSplitString<','>(intern, friends[a], true);
			m_friends.insert(boost::bimap<int, std::istring>::relation(atoi(intern.at(0).c_str()),
				std::istring(intern.at(1).c_str())));
		}
		for(size_t a = 0; a < ennemies.size(); ++a)
		{
			std::vector<std::string> intern;
			Desperion::FastSplitString<','>(intern, ennemies[a]);
			m_ennemies.insert(boost::bimap<int, std::istring>::relation(atoi(intern.at(0).c_str()),
				std::istring(intern.at(1).c_str())));
		}
		m_booleanValues[BOOL_FRIEND_WARN_ON_CONNECTION] = fields[3].GetBool();
		m_booleanValues[BOOL_FRIEND_WARN_ON_LEVEL_GAIN] = fields[4].GetBool();
		m_booleanValues[BOOL_GUILD_MEMBER_WARN_ON_CONNECTION] = fields[5].GetBool();
	}
	else
	{
		Desperion::eDatabase.AsyncExecute("INSERT INTO account_social VALUES(%u, '', '', 0, 0, 0);", m_data[FLAG_GUID].intValue);
		m_booleanValues[BOOL_FRIEND_WARN_ON_CONNECTION] = false;
		m_booleanValues[BOOL_FRIEND_WARN_ON_LEVEL_GAIN] = false;
		m_booleanValues[BOOL_GUILD_MEMBER_WARN_ON_CONNECTION] = false;
	}
	

	uint16 servID = Desperion::Config::Instance().GetParam(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT);
	Desperion::eDatabase.AsyncExecute("UPDATE accounts SET ticket='', logged=%u, lastServer=%u, lastIP='%s', lastConnectionDate=%llu WHERE guid=%u \
								 LIMIT 1;", servID, servID, m_socket->remote_endpoint().address().to_string().c_str(), time(NULL),
								 m_data[FLAG_GUID].intValue);

	World::Instance().AddSession(this);
	LOG("***** Connection with IP address %s {%s} *****", m_socket->remote_endpoint().address().to_string().c_str(),
		Desperion::FormatTime("%x").c_str());

	Send(AuthenticationTicketAcceptedMessage());
	Send(AccountCapabilitiesMessage(m_data[FLAG_GUID].intValue, false, 0x1fff, 0x1fff));
	std::vector<int16> features;
	features.push_back(1); // ankabox
	features.push_back(2); // kolizéum
	Send(ServerOptionalFeaturesMessage(features));
	Send(BasicTimeMessage(static_cast<int>(time(NULL)), 0));
	Send(BasicNoOperationMessage());
	Send(TrustStatusMessage(true));
}

void Session::Save()
{
	if(m_data[FLAG_GUID].intValue != 0)
	{
		std::ostringstream channels, disallowed;
		for(std::set<int8>::iterator it = m_channels.begin(); it != m_channels.end(); ++it)
		{
			if(it != m_channels.begin())
				channels<<",";
			channels<<int16(*it);
		}
		for(std::set<int8>::iterator it = m_disallowed.begin(); it != m_disallowed.end(); ++it)
		{
			if(it != m_disallowed.begin())
				disallowed<<",";
			disallowed<<int16(*it);
		}
		Desperion::eDatabase.Execute("UPDATE accounts SET logged=0, channels='%s', disallowed='%s' WHERE guid=%u LIMIT 1;",
			channels.str().c_str(), disallowed.str().c_str(), m_data[FLAG_GUID].intValue);

		std::ostringstream friends, ennemies;
		for(boost::bimap<int, std::istring>::iterator it = m_friends.begin(); it != m_friends.end(); ++it)
		{
			if(it != m_friends.begin())
				friends<<";";
			friends<<it->get_left()<<","<<it->get_right().c_str();
		}
		for(boost::bimap<int, std::istring>::iterator it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
		{
			if(it != m_ennemies.begin())
				ennemies<<";";
			ennemies<<it->get_left()<<","<<it->get_right().c_str();
		}
		Desperion::eDatabase.AsyncExecute("UPDATE account_social SET friends='%s', ennemies='%s', friendWarnOnConnection=%u, \
									  friendWarnOnLevelGain=%u, guildMemberWarnOnConnection=%u WHERE guid=%u LIMIT 1;",
									  friends.str().c_str(), ennemies.str().c_str(), m_booleanValues[BOOL_FRIEND_WARN_ON_CONNECTION],
									  m_booleanValues[BOOL_FRIEND_WARN_ON_LEVEL_GAIN], m_booleanValues[BOOL_GUILD_MEMBER_WARN_ON_CONNECTION],
									  m_data[FLAG_GUID].intValue);

		if(m_char != NULL)
		{
			m_char->Save();
			CharacterMinimals* cm = World::Instance().GetCharacterMinimals(m_char->GetGuid());
			Desperion::sDatabase.AsyncExecute("UPDATE character_minimals SET lastConnectionDate=%llu WHERE id=%u LIMIT 1;",
				cm->lastConnectionDate, cm->id);
		}
	}
}

Session::~Session()
{
	Save();
	if(m_data[FLAG_GUID].intValue != 0)
	{
		World::Instance().DeleteSession(m_data[FLAG_GUID].intValue);
		LOG("***** Disconnection *****");
		if(m_char != NULL)
		{
			if(m_party != NULL)
			{
				INIT_PARTY_LOCK
				PARTY_LOCK(m_party)
				m_party->Delete(&Party::m_players, m_char->GetGuid());
				m_party->IntegrityCheck(lock);
			}
			for(std::map<int, Session*>::iterator it = m_partyInvitations.begin(); it != m_partyInvitations.end(); ++it)
			{
				it->second->Send(PartyRefuseInvitationNotificationMessage(it->first, m_char->GetGuid()));
				if(it->second->m_party == NULL)
					continue; // ne devrait pas arriver non plus
				INIT_PARTY_LOCK
				PARTY_LOCK(it->second->m_party)
				it->second->m_party->Delete(&Party::m_guests, m_char->GetGuid());
				it->second->m_party->IntegrityCheck(lock);
			}

			m_char->GetMap()->RemoveActor(m_char->GetGuid());
			delete m_char;
		}
	}
}

void Session::Start()
{
	Send(ProtocolRequired(PROTOCOL_BUILD, PROTOCOL_REQUIRED_BUILD));
	Send(HelloGameMessage());

	Run();
}