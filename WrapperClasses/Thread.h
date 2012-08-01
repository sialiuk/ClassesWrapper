#pragma once
#include <boost\function.hpp>
#include <boost\noncopyable.hpp>
#include <Windows.h>
#include <exception>

namespace wrapper
{
	
	class Thread
		: private boost::noncopyable
	{
		typedef boost::function<void ()> Func;
		typedef boost::function<void (std::exception_ptr)> FuncExcept;

		struct ThreadRoutine
		{
			ThreadRoutine(const Func&, const FuncExcept&);
			Func m_routine;
			FuncExcept m_callback;
		};

	public:
		explicit Thread(const Func&, unsigned = 0, const FuncExcept& = CallbackDefault);
		~Thread();
		void Swap(Thread&);
		void Join();
		bool Joinable() const;
		unsigned GetThreadId() const;
		void Interrupt();
		void StartThread();
	private:
		static unsigned int __stdcall Callable(void*);
		static void CallbackDefault(std::exception_ptr);
	private:
		ThreadRoutine m_threadRoutine;
		HANDLE m_threadHandle;
		unsigned m_threadId;
	};
}