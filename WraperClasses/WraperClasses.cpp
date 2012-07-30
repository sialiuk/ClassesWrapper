// WraperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Thread.h"


int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread([](){ std::cout << "123\n"; });
	thread.Join();
	return 0;
}

