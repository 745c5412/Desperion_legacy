#ifndef __SINGLETON__
#define __SINGLETON__

template<class T>
class Singleton
{
public:
	Singleton() 
	{
		assert(m_singleton == NULL);
		m_singleton = static_cast<T*>(this);
	}

	virtual ~Singleton() 
	{ m_singleton = NULL; }

	static T& Instance()
	{
		assert(m_singleton);
		return *m_singleton;
	}

	static T* InstancePtr()
	{
		assert(m_singleton);
		return m_singleton;
	}

protected:
	static T* m_singleton;
};

#endif
