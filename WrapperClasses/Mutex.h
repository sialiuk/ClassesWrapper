#pragma once
#include <boost\noncopyable.hpp>
#include <Windows.h>

namespace wrapper
{
	class Mutex
		: private boost::noncopyable
	{
		friend class ConditionVariable;
	public:
		Mutex();
		~Mutex();
		void Lock();
		void UnLock();
	private:
		CRITICAL_SECTION m_section;
	};
}