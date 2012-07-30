#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <stdexcept>

namespace wrapper
{
	unsigned int Thread::Callable(void* ptr)
	{
		auto f = static_cast<Func*>(ptr);
		try
		{
			(*f)();
		}
		catch(...)
		{
		}
		return 0;
	}

	Thread::Thread(const Func& f)
		: m_routine(f)
		, m_threadHandle(NULL)
	{
		m_threadHandle = (HANDLE)_beginthreadex(nullptr, 0, Thread::Callable, &m_routine, 0, 0);
		if(!m_threadHandle)
		{
			throw std::runtime_error("Error create thread");
		}
	}

	void Thread::Join()
	{
		DWORD a = WaitForSingleObject(m_threadHandle, INFINITE);
	}
}