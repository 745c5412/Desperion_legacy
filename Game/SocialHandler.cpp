#include "StdAfx.h"

void Session::HandleFriendsGetListMessage(ByteBuffer& data)
{
	std::vector<FriendInformationsPtr> list;
	for(std::set<std::string>::iterator it = m_friends.begin(); it != m_friends.end(); ++it)
	{
		Session* S = World::Instance().GetSession(*it);
		if(S != NULL && S->GetCharacter() != NULL)
		{
			list.push_back(FriendInformationsPtr(new FriendOnlineInformations(S->GetData(FLAG_GUID).intValue,
				S->GetData(FLAG_PSEUDO).stringValue, S->GetCharacter()->GetContextType(), 0, S->GetCharacter()->GetName(),
				S->GetCharacter()->GetLevel(), S->GetCharacter()->GetStats().GetAlignmentSide(), S->GetCharacter()->GetBreed(),
				S->GetCharacter()->GetSex(), S->GetCharacter()->GetSmileyId())));
		}
		else
		{
			ResultPtr QR = Desperion::eDatabase->Query("SELECT guid, pseudo, lastConnectionDate FROM accounts WHERE LOWER(pseudo)='%s' LIMIT 1;",
				(*it).c_str());
			if(QR)
			{
				Field* fields = QR->Fetch();
				list.push_back(FriendInformationsPtr(new FriendInformations(fields[0].GetInt32(), fields[1].GetString(),
					0, fields[3].GetInt32())));
			}
		}
	}
}