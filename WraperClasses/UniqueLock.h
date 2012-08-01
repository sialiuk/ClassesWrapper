#pragma once

namespace wrapper
{
	template<typename Lock>
	class UniqueLock
	{
		friend class ConditionVariable;
	public:
		UniqueLock(Lock& m)
			: m_mutex(m)
		{
			m_mutex.Lock();
		}
		~UniqueLock()
		{
			m_mutex.UnLock();
		}
	private:
		Lock& m_mutex;
	};
}