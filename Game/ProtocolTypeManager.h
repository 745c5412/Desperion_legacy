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

#ifndef __PROTOCOL_TYPE_MANAGER__
#define __PROTOCOL_TYPE_MANAGER__

class EntityDispositionInformations;
class HumanInformations;
class ObjectEffect;
class GameRolePlayActorInformations;
class IgnoredInformations;
class FriendInformations;
class CharacterBaseInformations;
class HouseInformations;
class InteractiveElementSkill;
class FightTeamInformations;
class FightTeamMemberInformations;
class PartyInvitationMemberInformations;
class IdentifiedEntityDispositionInformations;
class GameFightMinimalStats;
class GameFightFighterInformations;

namespace Desperion
{
	namespace ProtocolTypeManager
	{
		EntityDispositionInformations* GetEntityDispositionInformations(uint16);
		HumanInformations* GetHumanInformations(uint16);
		ObjectEffect* GetObjectEffect(uint16);
		GameRolePlayActorInformations* GetGameRolePlayActorInformations(uint16);
		IgnoredInformations* GetIgnoredInformations(uint16);
		FriendInformations* GetFriendInformations(uint16);
		CharacterBaseInformations* GetCharacterBaseInformations(uint16);
		HouseInformations* GetHouseInformations(uint16);
		InteractiveElementSkill* GetInteractiveElementSkill(uint16);
		FightTeamInformations* GetFightTeamInformations(uint16);
		FightTeamMemberInformations* GetFightTeamMemberInformations(uint16);
		PartyInvitationMemberInformations* GetPartyInvitationMemberInformations(uint16);
		IdentifiedEntityDispositionInformations* GetIdentifiedEntityDispositionInformations(uint16);
		GameFightMinimalStats* GetGameFightMinimalStats(uint16);
		GameFightFighterInformations* GetGameFightFighterInformations(uint16);
	}
}

#endif