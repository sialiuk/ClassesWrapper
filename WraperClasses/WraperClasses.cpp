// WraperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thread.h"


int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread1([](){ std::cout << "123 "; });
	thread1.Join();
	std::cout << thread1.GetThreadId() << std::endl;
	wrapper::Thread thread2([](){ std::cout << "456 "; });
	thread2.Join();
	std::cout << thread2.GetThreadId() << std::endl;
	wrapper::Thread thread3([](){ std::cout << "789 "; });
	thread3.Join();
	std::cout << thread3.GetThreadId() << std::endl;

	wrapper::Thread threadSuspend([](){ std::cout << "789 "; }, CREATE_SUSPENDED);
	threadSuspend.StartThread();
	threadSuspend.Join();
	std::cout << threadSuspend.GetThreadId() << std::endl;
	return 0;
}

