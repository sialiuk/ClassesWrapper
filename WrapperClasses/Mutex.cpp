#include "stdafx.h"
#include "Mutex.h"

namespace wrapper
{
	Mutex::Mutex()
	{
		InitializeCriticalSection(&m_section);
	}

	Mutex::~Mutex()
	{
		DeleteCriticalSection(&m_section);
	}

	void Mutex::Lock()
	{
		EnterCriticalSection(&m_section);
	}

	void Mutex::UnLock()
	{
		LeaveCriticalSection(&m_section);
	}
}