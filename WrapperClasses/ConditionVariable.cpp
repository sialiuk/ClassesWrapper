#include "stdafx.h"
#include "ConditionVariable.h"
#include <boost\format.hpp>
#include <stdexcept>

namespace wrapper
{
	ConditionVariable::ConditionVariable()
	{
		InitializeConditionVariable(&m_condVariable);
	}

	void ConditionVariable::Wait(Locker& lock)
	{
		BOOL result = SleepConditionVariableCS(&m_condVariable, &lock.m_mutex.m_section, INFINITE);
		if(!result)
		{
			throw std::runtime_error((boost::format("Wait Conditionvariable is failed, error: %1%") 
										% GetLastError()).str());
		}
	}

	bool ConditionVariable::TimedWait(Locker& lock, unsigned long milliseconds)
	{
		BOOL result = SleepConditionVariableCS(&m_condVariable, &lock.m_mutex.m_section, milliseconds);
		if(!result)
		{
			DWORD error = GetLastError();
			if(error != ERROR_TIMEOUT)
			{
				throw std::runtime_error((boost::format("Wait Conditionvariable is failed, error: %1%") 
										% error).str());
			}
		}
		return (result ? true : false);
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