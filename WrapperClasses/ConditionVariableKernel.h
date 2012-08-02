#pragma once
#include "UniqueLock.h"
#include "MutexKernel.h"

namespace wrapper
{
	class ConditionVariableKernel
		: private boost::noncopyable
	{
		typedef UniqueLock<MutexKernel> Locker;
		
		class Relocker
		{
		public:
			Relocker(Locker&);
			~Relocker();
		private:
			Locker& m_lock;
		};
		
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