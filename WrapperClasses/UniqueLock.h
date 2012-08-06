#pragma once

namespace wrapper
{
	template<typename T>
	class UniqueLock
	{
		friend class ConditionVariable;
	public:
		explicit UniqueLock(T& m)
			: m_mutex(m)
		{
			m_mutex.Lock();
		}

		~UniqueLock()
		{
			m_mutex.UnLock();
		}

		void Lock()
		{
			m_mutex.Lock();
		}

		void UnLock()
		{
			m_mutex.UnLock();
		}
	private:
		T& m_mutex;
	};
}