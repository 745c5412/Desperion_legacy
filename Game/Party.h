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

public:
	std::list<Session*> m_players;
	std::list<Session*> m_guests;

	Party()
	{
	}

	void IntegrityCheck(boost::shared_ptr<boost::mutex::scoped_lock>);
	void FillMembers(std::vector<PartyMemberInformationsPtr>&);
	void FillInvitationMembers(std::vector<PartyInvitationMemberInformationsPtr>&);
	void FillGuests(std::vector<PartyGuestInformationsPtr>&);
	std::list<Session*>::iterator Get(std::list<Session*> Party::*, int);
	void Delete(std::list<Session*> Party::*, int, bool isGuestCancel = false);
	void Send(DofusMessage&, int self = -1);

	void Push(std::list<Session*> Party::*list, Session* s)
	{ (this->*list).push_back(s); }

	void Erase(std::list<Session*> Party::*list, std::list<Session*>::iterator it)
	{ (this->*list).erase(it); }

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

	std::list<Session*>::iterator End(std::list<Session*> Party::*list)
	{ return (this->*list).end(); }
};

#endif