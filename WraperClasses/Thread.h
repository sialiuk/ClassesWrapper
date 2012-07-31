#pragma once
#include <boost\function.hpp>
#include <boost\noncopyable.hpp>
#include <Windows.h>

namespace wrapper
{
	
	class Thread
		: private boost::noncopyable
	{
		typedef boost::function<void ()> Func;
	public:
		explicit Thread(const Func&, unsigned = 0);
		~Thread();
		void Swap(Thread&);
		void Join();
		unsigned GetThreadId() const;
		void Interrupt();
		void StartThread();
	private:
		static unsigned int __stdcall Callable(void*);
	private:
		Func m_routine;
		HANDLE m_threadHandle;
		unsigned m_threadId;
	};
}