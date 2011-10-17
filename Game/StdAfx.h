/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __STDAFX__
#define __STDAFX__

#include "../Shared/StdAfx.h"

#include "ConfigDefaults.h"
#include "World.h"
#include "Master.h"
#include "Item.h"
#include "Weapon.h"
#include "CharacterMinimals.h"

#include "CharacterBaseCharacteristic.h"
#include "CharacterStats.h"

#include "PlayerItem.h"
#include "Map.h"
#include "GameClient.h"

#include "EntityLook.h"
#include "CharacterMinimalInformations.h"
#include "CharacterMinimalPlusLookInformations.h"
#include "CharacterBaseInformations.h"
#include "AuthenticationTicketMessage.h"
#include "AuthenticationTicketRefusedMessage.h"
#include "AuthenticationTicketAcceptedMessage.h"
#include "AccountCapabilitiesMessage.h"
#include "CharactersListRequestMessage.h"
#include "CharactersListMessage.h"
#include "CharacterDeletionRequestMessage.h"
#include "CharacterDeletionErrorMessage.h"
#include "CharacterNameSuggestionRequestMessage.h"
#include "ServerOptionalFeaturesMessage.h"
#include "HelloGame.h"
#include "CharacterNameSuggestionFailureMessage.h"
#include "CharacterNameSuggestionSuccessMessage.h"
#include "CharacterSelectionMessage.h"
#include "CharacterSelectedErrorMessage.h"
#include "CharacterSelectedSuccessMessage.h"
#include "CharacterCreationRequestMessage.h"
#include "EntityDispositionInformations.h"
#include "GameContextActorInformations.h"
#include "GameRolePlayActorInformations.h"
#include "GameRolePlayNamedActorInformations.h"
#include "ActorRestrictionsInformations.h"
#include "HumanInformations.h"
#include "GameRolePlayHumanoidInformations.h"
#include "ActorAlignmentInformations.h"
#include "GameRolePlayCharacterInformations.h"
#include "GameContextDestroyMessage.h"
#include "GameContextCreateRequestMessage.h"
#include "GameContextCreateMessage.h"
#include "InventoryContentMessage.h"
#include "InventoryWeightMessage.h"
#include "CurrentMapMessage.h"
#include "TextInformationMessage.h"
#include "MapInformationsRequestMessage.h"
#include "CharacterCharacteristicsInformations.h"
#include "ActorExtendedAlignmentInformations.h"
#include "GameMapMovementRequestMessage.h"
#include "GameMapMovementMessage.h"
#include "GameMapMovementConfirmMessage.h"
#include "ChangeMapMessage.h"
#include "BasicNoOperationMessage.h"
#include "AdminCommandMessage.h"
#include "AdminQuietCommandMessage.h"
#include "GameContextRemoveElementMessage.h"

#include "Entity.h"
#include "Character.h"
#include "CharacterStatsListMessage.h"
#include "MapComplementaryInformationsDataMessage.h"
#include "GameRolePlayShowActorMessage.h"
#include "Session.h"

#endif