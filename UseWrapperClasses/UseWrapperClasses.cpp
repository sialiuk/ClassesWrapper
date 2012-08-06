// UseWrapperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include "..\WrapperClasses\Thread.h"
#include "..\WrapperClasses\Mutex.h"
#include "..\WrapperClasses\ConditionVariable.h"

namespace
{
	std::string str;
	void Write(const std::string& ch)
	{
		str += ch;
	}

	void Print()
	{
		std::cout << str << std::endl;
	}

	wrapper::Mutex g_mutex, g_cmutex;
	wrapper::ConditionVariable g_printVariable, g_writeVariable;

	auto funcPrint = []()
	{
		wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
		g_printVariable.Wait(lock);
		Print();
	};

	auto funcWriteLast = []()
	{
		wrapper::UniqueLock<wrapper::Mutex> lock(g_cmutex);
		g_writeVariable.TimedWait(lock, 1000);
		Write("test");
		g_printVariable.NotifyAll();
	};

	auto funcWriteFirst = []()
	{
		wrapper::UniqueLock<wrapper::Mutex> lock(g_cmutex);
		Write("Crash ");
		g_writeVariable.NotifyOne();
	};
}

int _tmain(int argc, _TCHAR* argv[])
{
	typedef wrapper::Thread Thread;
	typedef std::shared_ptr<Thread> ThreadPtr;
	std::vector<ThreadPtr> pool;
	for(size_t i = 0; i != 7; ++i)
	{
		pool.push_back(std::make_shared<Thread>(funcPrint));
	}
	
	pool.push_back(std::make_shared<Thread>(funcWriteLast));
	pool.push_back(std::make_shared<Thread>(funcWriteFirst));

	for(size_t i = 0; i != pool.size(); ++i)
	{
		pool[i]->Join();
	}
	
	return 0;
}

