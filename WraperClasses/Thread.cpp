#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <stdexcept>

namespace wrapper
{
	unsigned int Thread::Callable(void* ptr)
	{
		Func* f = static_cast<Func*>(ptr);
		try
		{
			(*f)();
		}
		catch(...)
		{

		}
		return 0;
	}

	Thread::Thread(const Func& f, unsigned initFlag)
		: m_routine(f)
		, m_threadHandle(NULL)
		, m_threadId(0)
	{
		m_threadHandle = (HANDLE)_beginthreadex(nullptr, 0, Thread::Callable, &m_routine, initFlag, &m_threadId);
		if(!m_threadHandle)
		{
			throw std::runtime_error("Error create thread");
		}
	}

	Thread::~Thread()
	{
		CloseHandle(m_threadHandle);
	}

	void Thread::Swap(Thread& other)
	{
		std::swap(m_routine, other.m_routine);
		std::swap(m_threadHandle, other.m_threadHandle);
		std::swap(m_threadId, other.m_threadId);
	}

	void Thread::Join()
	{
		WaitForSingleObject(m_threadHandle, INFINITE);
	}

	unsigned Thread::GetThreadId() const
	{
		return m_threadId;
	}

	void Thread::Interrupt()
	{
		SuspendThread(m_threadHandle);
	}

	void Thread::StartThread()
	{
		ResumeThread(m_threadHandle);
	}
}