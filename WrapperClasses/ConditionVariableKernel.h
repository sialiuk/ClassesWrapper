#pragma once
#include "UniqueLock.h"
#include "MutexKernel.h"

namespace wrapper
{
	class ConditionVariableKernel
	{
		typedef UniqueLock<MutexKernel> Locker;
	public:
		ConditionVariableKernel();
		~ConditionVariableKernel();
		void Wait(Locker&);
		void NotifyOne();
		void NotifyAll();
	private:
		HANDLE m_h[2];
		HANDLE& m_eventManualReset;
		HANDLE& m_eventAutomaticReset;
	};
}