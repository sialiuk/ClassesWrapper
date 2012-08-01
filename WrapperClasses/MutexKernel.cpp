#include "stdafx.h"
#include "MutexKernel.h"
#include <stdexcept>

namespace wrapper
{
	MutexKernel::MutexKernel()
		: m_mtx(NULL)
	{
		m_mtx = CreateMutex(NULL, FALSE, NULL);
		if(m_mtx == NULL)
		{
			throw std::runtime_error("Create MutexKernel failed");
		}
	}

	MutexKernel::~MutexKernel()
	{
		CloseHandle(m_mtx);
	}

	void MutexKernel::Lock()
	{
		WaitForSingleObject(m_mtx, INFINITE);
	}

	void MutexKernel::UnLock()
	{
		ReleaseMutex(m_mtx);
	}
}