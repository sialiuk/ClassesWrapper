#include "stdafx.h"
#include "ConditionVariable.h"

namespace wrapper
{
	ConditionVariable::ConditionVariable()
	{
		InitializeConditionVariable(&m_condVariable);
	}

	void ConditionVariable::Wait(Lock& lock)
	{
		SleepConditionVariableCS(&m_condVariable, &lock.m_mutex.m_section, INFINITE);
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