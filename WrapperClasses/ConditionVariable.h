#pragma once
#include "UniqueLock.h"
#include "Mutex.h"
#include <Windows.h>

namespace wrapper
{
	class ConditionVariable
		: private boost::noncopyable
	{
		typedef UniqueLock<Mutex> Locker;
	public:
		ConditionVariable();
		void Wait(Locker&);
		bool TimedWait(Locker&, unsigned long);
		template<typename Predicate>
			void Wait(Locker&, Predicate);
		void NotifyOne();
		void NotifyAll();
	private:
		CONDITION_VARIABLE m_condVariable;
	};
}