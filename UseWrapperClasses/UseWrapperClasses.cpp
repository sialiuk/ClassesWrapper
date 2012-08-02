// UseWrapperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\WrapperClasses\Thread.h"
#include "..\WrapperClasses\MutexKernel.h"
#include "..\WrapperClasses\ConditionVariableKernel.h"

namespace
{
	std::string str;

	void Write(const char* ch)
	{
		str += ch;
	}

	void Print()
	{
		std::cout << str << std::endl;
	}

	wrapper::MutexKernel g_mutex;
	wrapper::ConditionVariableKernel g_printVariable, g_writeVariable;
}

int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread1(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});

	wrapper::Thread thread2(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});


	wrapper::Thread thread5(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});

	wrapper::Thread thread6(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});


	wrapper::Thread thread7(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});

	wrapper::Thread thread8(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
		});

	wrapper::Thread thread3(
		[&]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			g_writeVariable.Wait(lock);
			Write("test");
			g_printVariable.NotifyAll();
		});

	wrapper::Thread thread4(
		[]()
		{
			wrapper::UniqueLock<wrapper::MutexKernel> lock(g_mutex);
			Write("Crash ");
			g_writeVariable.NotifyOne();
		});

	thread1.Join();
	std::cout << thread1.GetThreadId() << std::endl;
	thread2.Join();
	std::cout << thread2.GetThreadId() << std::endl;
	thread5.Join();
	std::cout << thread5.GetThreadId() << std::endl;
	thread6.Join();
	std::cout << thread6.GetThreadId() << std::endl;
	thread7.Join();
	std::cout << thread7.GetThreadId() << std::endl;
	thread8.Join();
	std::cout << thread8.GetThreadId() << std::endl;
	
	return 0;
}

