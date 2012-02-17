#ifndef __PARTY__
#define __PARTY__

#define INIT_PARTY_LOCK boost::shared_ptr<boost::mutex::scoped_lock> lock;
#define PARTY_LOCK(x) lock.reset(new boost::mutex::scoped_lock(x->GetMutex()));

struct Party
{
private:
	boost::mutex m_lock;
	int m_partyId;
	Session* m_leader;
	std::map<int, int> m_guestHosts;
	std::list<Session*> m_players;
	std::list<Session*> m_guests;
	
	void _Push(std::list<Session*> Party::*list, Session* s)
	{ (this->*list).push_back(s); }

	void _Erase(std::list<Session*> Party::*list, std::list<Session*>::iterator it)
	{ (this->*list).erase(it); }
	
	std::list<Session*>::iterator _Get(std::list<Session*> Party::*, int);
	void _Delete(std::list<Session*> Party::*, int, bool isGuestCancel = false);
public:

	Party()
	{}

	void IntegrityCheck(boost::shared_ptr<boost::mutex::scoped_lock>);
	void FillMembers(std::vector<PartyMemberInformationsPtr>&);
	void FillInvitationMembers(std::vector<PartyInvitationMemberInformationsPtr>&);
	void FillGuests(std::vector<PartyGuestInformationsPtr>&);
	void Send(const DofusMessage&, int self = -1);
	
	std::list<Session*>::iterator GuestGet(int id)
	{ return _Get(&Party::m_guests, id); }
	
	void GuestDelete(int id, bool isGuestCancel = false)
	{ _Delete(&Party::m_guests, id, isGuestCancel); }
	
	void PlayerDelete(int id, bool isGuestCancel = false)
	{ _Delete(&Party::m_players, id, isGuestCancel); }
	
	std::list<Session*>::iterator PlayerGet(int id)
	{ return _Get(&Party::m_players, id); }
	
	void GuestPush(Session* s)
	{ _Push(&Party::m_guests, s); }
	
	void PlayerPush(Session* s)
	{ _Push(&Party::m_players, s); }

	size_t PlayersSize() const
	{ return m_players.size(); }

	size_t GuestsSize() const
	{ return m_guests.size(); }
	
	void GuestErase(std::list<Session*>::iterator it)
	{ _Erase(&Party::m_guests, it); }
	
	void PlayerErase(std::list<Session*>::iterator it)
	{ _Erase(&Party::m_players, it); }

	void SetGuestHost(int guest, int id)
	{ m_guestHosts[guest] = id; }

	int GetPartyId() const
	{ return m_partyId; }

	void SetPartyId(int id)
	{ m_partyId = id; }

	Session* GetLeader()
	{ return m_leader; }

	void SetLeader(Session* s)
	{ m_leader = s; }

	boost::mutex& GetMutex()
	{ return m_lock; }
	
	std::list<Session*>::iterator GuestsEnd()
	{ return m_guests.end(); }
	
	std::list<Session*>::iterator PlayersEnd()
	{ return m_players.end(); }
};

#endif