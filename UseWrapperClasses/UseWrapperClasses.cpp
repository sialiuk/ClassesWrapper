// UseWrapperClasses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\WrapperClasses\Thread.h"

int _tmain(int argc, _TCHAR* argv[])
{
	wrapper::Thread thread1([](){});
	thread1.Join();
	return 0;
}

