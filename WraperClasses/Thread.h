#pragma once
#include <boost\function.hpp>
#include <boost\thread.hpp>
#include <Windows.h>

namespace wrapper
{
	typedef boost::function<void ()> Func;

	class Thread
	{
	public:
		Thread(const Func&);
		void Join();
	private:
		static unsigned int __stdcall Callable(void*);
	private:
		Func m_routine;
		HANDLE m_threadHandle;
	};
}