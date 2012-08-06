#include "stdafx.h"
#include "MutexKernel.h"
#include <boost\format.hpp>
#include <stdexcept>

namespace wrapper
{
	MutexKernel::MutexKernel()
		: m_mtx(NULL)
	{
		m_mtx = CreateMutex(NULL, FALSE, NULL);
		if(m_mtx == NULL)
		{
			throw std::runtime_error((boost::format("Create mutex is failed, error: %1%") 
										% GetLastError()).str());
		}
	}

	MutexKernel::~MutexKernel()
	{
		CloseHandle(m_mtx);
	}

	void MutexKernel::Lock()
	{
		DWORD result = WaitForSingleObject(m_mtx, INFINITE);
		if(result == WAIT_FAILED)
		{
			throw std::runtime_error((boost::format("Capture of mutex is failed, error: %1%")
										% GetLastError()).str());
		}
	}

	void MutexKernel::UnLock()
	{
		BOOL result = ReleaseMutex(m_mtx);
		if(!result)
		{
			throw std::runtime_error((boost::format("Release mutex is failed, error: %1%") 
										% GetLastError()).str());
		}
	}
}