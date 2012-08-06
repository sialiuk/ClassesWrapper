#include "stdafx.h"
#include "Thread.h"
#include <process.h>
#include <boost\format.hpp>
#include <stdexcept>

namespace wrapper
{
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

	Thread::ThreadRoutine::ThreadRoutine(const Func& f, const FuncExcept& ex)
		: m_routine(f)
		, m_callback(ex)
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
			throw std::runtime_error((boost::format("Create thread is failed, error: %1%") 
										% GetLastError()).str());
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
		DWORD result = WaitForSingleObject(m_threadHandle, INFINITE);
		if(result == WAIT_FAILED)
		{
			throw std::runtime_error((boost::format("Waiting for thread is failed, error: %1%")
										% GetLastError()).str());
		}
	}

	bool Thread::Joinable() const
	{
		DWORD exitCode(0);
		BOOL result = GetExitCodeThread(m_threadHandle, &exitCode);
		if(!result)
		{
			throw std::runtime_error((boost::format("Get exit code thread is failed, error: %1%") 
										% GetLastError()).str());
		}

		if(exitCode == STILL_ACTIVE)
		{
			return false;
		}
		return true;
	}

	unsigned Thread::GetThreadId() const
	{
		return m_threadId;
	}

	unsigned long Thread::Suspend()
	{
		return SuspendThread(m_threadHandle);
	}

	void Thread::Interrupt()
	{
		if(!Joinable())
		{
			if(!TerminateThread(m_threadHandle, -1))
			{
				throw std::runtime_error((boost::format("Terminate thread is failed, error: %1%") 
										% GetLastError()).str());
			}
		}
	}

	unsigned long Thread::StartThread()
	{
		return ResumeThread(m_threadHandle);
	}
}