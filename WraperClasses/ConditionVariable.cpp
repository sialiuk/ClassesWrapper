#include "stdafx.h"
#include "ConditionVariable.h"

namespace wrapper
{
	ConditionVariable::ConditionVariable()
	{
		InitializeConditionVariable(&m_condVariable);
	}

	void ConditionVariable::Wait(Locker& lock)
	{
		SleepConditionVariableCS(&m_condVariable, &lock.m_mutex.m_section, INFINITE);
	}

	template<typename Predicate>
	void ConditionVariable::Wait(Locker& lock, Predicate pred)
	{
		while(!pred())
		{
			Wait(lock);
		}
	}

	void ConditionVariable::NotifyOne()
	{
		WakeConditionVariable(&m_condVariable);
	}

	void ConditionVariable::NotifyAll()
	{
		WakeAllConditionVariable(&m_condVariable);
	}
}