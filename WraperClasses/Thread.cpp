#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <stdexcept>

namespace wrapper
{
	Thread::ThreadRoutine::ThreadRoutine(const Func& f, const FuncExcept& ex)
		: m_routine(f)
		, m_callback(ex)
	{
	}

	unsigned int Thread::Callable(void* ptr)
	{
		ThreadRoutine* f = static_cast<ThreadRoutine*>(ptr);
		try
		{
			f->m_routine();
		}
		catch(...)
		{
			f->m_callback(std::current_exception());
		}
		return 0;
	}

	void Thread::CallbackDefault(std::exception_ptr)
	{
	}

	Thread::Thread(const Func& f, unsigned initFlag, const FuncExcept& ex)
		: m_threadRoutine(f, ex)
		, m_threadHandle(NULL)
		, m_threadId(0)
	{
		m_threadHandle = (HANDLE)_beginthreadex(nullptr, 0, Thread::Callable, &m_threadRoutine, initFlag, &m_threadId);
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
		std::swap(m_threadRoutine, other.m_threadRoutine);
		std::swap(m_threadHandle, other.m_threadHandle);
		std::swap(m_threadId, other.m_threadId);
	}

	void Thread::Join()
	{
		WaitForSingleObject(m_threadHandle, INFINITE);
	}

	bool Thread::Joinable() const
	{
		DWORD exitCode(0);
		GetExitCodeThread(m_threadHandle, &exitCode);
		if(exitCode == STILL_ACTIVE)
		{
			return false;
		}
		else
		{
			return true;
		}
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