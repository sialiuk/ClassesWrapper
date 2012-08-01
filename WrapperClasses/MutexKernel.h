#pragma once
#include <boost\noncopyable.hpp>
#include <Windows.h>

namespace wrapper
{
	class MutexKernel
		: private boost::noncopyable
	{
	public:
		MutexKernel();
		~MutexKernel();
		void Lock();
		void UnLock();
	private:
		HANDLE m_mtx;
	};
}