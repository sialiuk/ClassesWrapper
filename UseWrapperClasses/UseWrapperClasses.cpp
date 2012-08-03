// UseWrapperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "..\WrapperClasses\Thread.h"
#include "..\WrapperClasses\Mutex.h"
#include "..\WrapperClasses\ConditionVariable.h"

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

	wrapper::Mutex g_mutex, g_cmutex;
	wrapper::ConditionVariable g_printVariable, g_writeVariable;
}

int _tmain(int argc, _TCHAR* argv[])
{
	typedef std::shared_ptr<wrapper::Thread> ThreadPtr;
	std::vector<ThreadPtr> pool;
	
	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_mutex);
			g_printVariable.Wait(lock);
			Print();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_cmutex);
			g_writeVariable.Wait(lock);
			Write("test");
			g_printVariable.NotifyAll();
	}));

	pool.push_back(std::make_shared<wrapper::Thread>([]()
		{
			wrapper::UniqueLock<wrapper::Mutex> lock(g_cmutex);
			Write("Crash ");
			g_writeVariable.NotifyOne();
	}));

	for(size_t i = 0; i != pool.size(); ++i)
	{
		pool[i]->Join();
	}

	return 0;
}

