#include "stdafx.h"
#include "ConditionVariableKernel.h"
#include <stdexcept>

namespace wrapper
{
	ConditionVariableKernel::ConditionVariableKernel()
		: m_eventManualReset( m_h[0])
		, m_eventAutomaticReset( m_h[1])
	{
		m_eventManualReset = CreateEvent(NULL, TRUE, FALSE, NULL);
		if(m_eventManualReset == NULL)
		{
			throw std::runtime_error("Create ConditionVariable failed");	
		}
		m_eventAutomaticReset = CreateEvent(NULL, FALSE, FALSE, NULL);
		if(m_eventAutomaticReset == NULL)
		{
			CloseHandle(m_eventManualReset);
			throw std::runtime_error("Create ConditionVariable failed");	
		}
		
	}
		
	ConditionVariableKernel::~ConditionVariableKernel()
	{
		CloseHandle(m_eventManualReset);
		CloseHandle(m_eventAutomaticReset);
	}

	void ConditionVariableKernel::Wait(Locker& lock)
	{
		lock.UnLock();
		WaitForMultipleObjects(2, m_h, FALSE, INFINITE);
		lock.Lock();
	}
	
	void ConditionVariableKernel::NotifyOne()
	{
		SetEvent(m_eventAutomaticReset);
	}

	void ConditionVariableKernel::NotifyAll()
	{
		SetEvent(m_eventManualReset);
	}
}