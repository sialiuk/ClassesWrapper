// WraperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thread.h"

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

int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread1([](){ std::cout << "123 "; });
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
									, 0, Exceptioncallback);
	threadSuspend.StartThread();
	threadSuspend.Join();
	std::cout << threadSuspend.GetThreadId() << std::endl;

	
	return 0;
}

