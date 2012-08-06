#include "stdafx.h"
#include "ConditionVariableKernel.h"
#include <stdexcept>
#include <boost\format.hpp>

namespace wrapper
{
	ConditionVariableKernel::Relocker::Relocker(Locker& l)
		:m_lock(l)
	{
		m_lock.UnLock();
	}

	ConditionVariableKernel::Relocker::~Relocker()
	{
		m_lock.Lock();
	}

	ConditionVariableKernel::ConditionVariableKernel()
		: m_eventManualReset( m_h[0])
		, m_eventAutomaticReset( m_h[1])
	{
		m_eventManualReset = CreateEvent(NULL, TRUE, FALSE, NULL);
		if(m_eventManualReset == NULL)
		{
			throw std::runtime_error((boost::format("Create ConditionVariable is failed, error: %1%") 
										% GetLastError()).str());
		}
		m_eventAutomaticReset = CreateEvent(NULL, FALSE, FALSE, NULL);
		if(m_eventAutomaticReset == NULL)
		{
			CloseHandle(m_eventManualReset);
			throw std::runtime_error((boost::format("Create ConditionVariable is failed, error: %1%") 
										% GetLastError()).str());	
		}
	}
		
	ConditionVariableKernel::~ConditionVariableKernel()
	{
		CloseHandle(m_eventManualReset);
		CloseHandle(m_eventAutomaticReset);
	}

	void ConditionVariableKernel::Wait(Locker& lock)
	{
		Relocker relock(lock);
		DWORD result = WaitForMultipleObjects(2, m_h, FALSE, INFINITE);
		if( result == WAIT_FAILED)
		{
			throw std::runtime_error((boost::format("Waiting ConditionVariable is failed, error: %1%")
										% GetLastError()).str());	
		}
	}
	
	bool ConditionVariableKernel::TimedWait(Locker& lock, unsigned long milliseconds)
	{
		Relocker relock(lock);
		DWORD result = WaitForMultipleObjects(2, m_h, FALSE, milliseconds);
		if(result == WAIT_TIMEOUT)
		{
			return false;
		}
		if( result == WAIT_FAILED)
		{
			throw std::runtime_error((boost::format("Waiting ConditionVariable is failed, error: %1%")
										% GetLastError()).str());	
		}
		return true;
	}

	void ConditionVariableKernel::NotifyOne()
	{
		BOOL result = SetEvent(m_eventAutomaticReset);
		if(!result)
		{
			throw std::runtime_error((boost::format("NotifyOne is failed, error: %1%")
										% GetLastError()).str());
		}
	}

	void ConditionVariableKernel::NotifyAll()
	{
		BOOL result = PulseEvent(m_eventManualReset);
		if(!result)
		{
			throw std::runtime_error((boost::format("NotifyAll is failed, error: %1%")
										% GetLastError()).str());
		}
	}
}