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

#ifndef __STDAFX__
#define __STDAFX__

#define GAME_VERSION_MAJOR 0
#define GAME_VERSION_MINOR 8
#define GAME_VERSION_REVISION 0

#define REQUIRED_SHARED_VERSION_MAJOR 0
#define REQUIRED_SHARED_VERSION_MINOR 0
#define REQUIRED_SHARED_VERSION_REVISION 2

#include "../Shared/StdAfx.h"

#include "ProtocolTypeManager.h"
#include "ConfigDefaults.h"
#include "World.h"
#include "Master.h"
#include "CharacterMinimals.h"
#include "ConditionsParser.h"
#include "DofusUtils.h"

#include "CharacterBaseCharacteristic.h"
#include "CharacterStats.h"

#include "ObjectEffect.h"
#include "ObjectEffectInteger.h"
#include "ObjectEffectDice.h"
#include "ObjectEffectCreature.h"
#include "ObjectEffectDate.h"
#include "ObjectEffectDuration.h"
#include "ObjectEffectLadder.h"
#include "ObjectEffectMinMax.h"
#include "ObjectEffectMount.h"
#include "ObjectEffectString.h"
#include "PlayerItem.h"
#include "Item.h"
#include "Weapon.h"
#include "Map.h"
#include "Path.h"
#include "GameClient.h"

#include "SubEntity.h"
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
#include "HelloGameMessage.h"
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
#include "DItem.h"
#include "ObjectItem.h"
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
#include "ConsoleCommandsListMessage.h"
#include "ConsoleMessage.h"
#include "GameContextRemoveElementMessage.h"
#include "ChatAbstractClientMessage.h"
#include "ChatAbstractServerMessage.h"
#include "ChatAdminServerMessage.h"
#include "ChatClientMultiMessage.h"
#include "ChatClientMultiWithObjectMessage.h"
#include "ChatClientPrivateMessage.h"
#include "ChatClientPrivateWithObjectMessage.h"
#include "ChatErrorMessage.h"
#include "ChatServerCopyMessage.h"
#include "ChatServerCopyWithObjectMessage.h"
#include "ChatServerMessage.h"
#include "ChatServerWithObjectMessage.h"
#include "GoldItem.h"
#include "GoldAddedMessage.h"
#include "LivingObjectChangeSkinRequestMessage.h"
#include "LivingObjectDissociateMessage.h"
#include "LivingObjectMessageMessage.h"
#include "LivingObjectMessageRequestMessage.h"
#include "ObjectAddedMessage.h"
#include "ObjectDeletedMessage.h"
#include "ObjectDeleteMessage.h"
#include "ObjectDropMessage.h"
#include "ObjectErrorMessage.h"
#include "ObjectFeedMessage.h"
#include "ObjectModifiedMessage.h"
#include "ObjectMovementMessage.h"
#include "ObjectQuantityMessage.h"
#include "ObjectsAddedMessage.h"
#include "ObjectsDeletedMessage.h"
#include "ObjectSetPositionMessage.h"
#include "ObjectItemQuantity.h"
#include "ObjectsQuantityMessage.h"
#include "ObjectUseMessage.h"
#include "ObjectUseMultipleMessage.h"
#include "ObjectUseOnCellMessage.h"
#include "ObjectUseOnCharacterMessage.h"
#include "SetUpdateMessage.h"
#include "GameContextRefreshEntityLookMessage.h"
#include "ObjectGroundAddedMessage.h"
#include "ObjectGroundListAddedMessage.h"
#include "ObjectGroundRemovedMessage.h"
#include "ObjectGroundRemovedMultipleMessage.h"
#include "CharacterCreationResultMessage.h"
#include "BasicPingMessage.h"
#include "BasicPongMessage.h"
#include "BasicTimeMessage.h"
#include "BasicDateMessage.h"
#include "../Login/ProtocolRequired.h"
#include "TrustStatusMessage.h"

#include "Mount.h"
#include "ItemSet.h"
#include "Entity.h"
#include "Character.h"
#include "CharacterStatsListMessage.h"
#include "MapComplementaryInformationsDataMessage.h"
#include "GameRolePlayShowActorMessage.h"
#include "Session.h"

#endif