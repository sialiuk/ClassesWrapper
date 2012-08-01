#pragma once
#include "UniqueLock.h"
#include "Mutex.h"
#include <Windows.h>

namespace wrapper
{
	class ConditionVariable
		: private boost::noncopyable
	{
		typedef UniqueLock<Mutex> Lock;
	public:
		ConditionVariable();
		void Wait(Lock&);
		void NotifyOne();
		void NotifyAll();
	private:
		CONDITION_VARIABLE m_condVariable;
	};
}