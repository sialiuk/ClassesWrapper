// WraperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thread.h"
#include "Mutex.h"
#include "UniqueLock.h"
#include "ConditionVariable.h"
#include <boost\thread\shared_mutex.hpp>

boost::shared_mutex m;

namespace
{
	int count = 0;
	wrapper::Mutex mutex;
	wrapper::ConditionVariable m_cond;
	void Exceptioncallback(std::exception_ptr ptr)
	{
		try
		{
			ptr._RethrowException();
		}
		catch(const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread1(
		[]()
		{
			{
				wrapper::UniqueLock<wrapper::Mutex> lock(mutex);
				m_cond.Wait(lock);
			}
			{
				wrapper::UniqueLock<wrapper::Mutex> lock(mutex);
				std::cout << count << std::endl; 
			}
		});
	wrapper::Thread thread2(
		[]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(mutex);
			count = 100;
			m_cond.NotifyOne();
		});
	thread1.Join();
	/*wrapper::Thread thread1([](){ std::cout << "123 "; });
	wrapper::Thread thread2([](){ std::cout << "456 "; });
	wrapper::Thread thread3([](){ std::cout << "789 "; });
	if(!thread1.Joinable())
		thread1.Join();
	std::cout << thread1.GetThreadId() << std::endl;
	
	if(!thread2.Joinable())
		thread2.Join();
	std::cout << thread2.GetThreadId() << std::endl;
	
	if(!thread3.Joinable())
		thread3.Join();
	std::cout << thread3.GetThreadId() << std::endl;

	wrapper::Thread threadSuspend([](){ std::cout << "789 "; throw std::runtime_error("Error!!!!!"); }
									, CREATE_SUSPENDED);
	threadSuspend.StartThread();
	threadSuspend.Join();
	std::cout << threadSuspend.GetThreadId() << std::endl;*/
	return 0;
}

