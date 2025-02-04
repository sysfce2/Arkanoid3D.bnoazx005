/*!
	\file CBaseJobManager.h
	\date 18.10.2018
	\authors Kasimov Ildar
*/

#pragma once


#include "IJobManager.h"
#include "CBaseObject.h"
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <memory>


namespace marl
{
	class Scheduler;
	class WaitGroup;
}


namespace TDEngine2
{
	struct TJobDecl
	{
		IJobManager* mpJobManager = nullptr;

		IJobManager::TJobCallback mJob = nullptr;
		TJobCounter* mpCounter = nullptr;
		U32 mJobIndex = 0;
		U32 mGroupIndex = 0;
		U32 mWaitingCounterThreshold = 0;
		const C8* mpJobName = "TDE2Job";
	};


	/*!
		\brief A factory function for creation objects of CResourceManager's type.

		\return A pointer to CResourceManager's implementation
	*/

	TDE2_API IJobManager* CreateBaseJobManager(const TJobManagerInitParams& desc, E_RESULT_CODE& result);


	/*!
		class CBaseJobManager

		\brief The class is a common implementation of a thread pool for
		Win32 and UNIX platforms
	*/

	class CBaseJobManager : public IJobManager, public CBaseObject
	{
		public:
			friend TDE2_API IJobManager* CreateBaseJobManager(const TJobManagerInitParams& desc, E_RESULT_CODE& result);
		protected:
			typedef std::queue<TJobDecl>              TJobQueue;
			typedef std::queue<std::function<void()>> TCallbacksQueue;
		public:
			/*!
				\brief The method initializes an inner state of a resource manager

				\param[in] desc A configuration of the job system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Init(const TJobManagerInitParams& desc) override;
			
			/*!
				\brief The method pushes specified job into a queue for an execution

				\param[in] pCounter A pointer to created object of counter. Can be nullptr if synchronization isn't needed
				\param[in] job A callback with the task that will be executed
				\param[in] params An optional parameters that can be specified for the job

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE SubmitJob(TJobCounter* pCounter, const TJobCallback& job, const TSubmitJobParams& params) override;

			/*!
				\brief The method is an equvivalent for "parallel_for" algorithm that splits some complex work between groups and
				executes the given job for all of them

				\param[in] pCounter A pointer to created object of counter. Can be nullptr if synchronization isn't needed
				\param[in] job A callback with the task that will be executed
				\param[in] priority The value determines into which queue the given job will be submited

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE SubmitMultipleJobs(TJobCounter* pCounter, U32 jobsCount, U32 groupSize, const TJobCallback& job, E_JOB_PRIORITY_TYPE priority = E_JOB_PRIORITY_TYPE::NORMAL) override;

			/*!
				\brief The function represents an execution barrier to make sure that any dependencies are finished to the point

				\param[in, out] counter A reference to syncronization context
			*/

			TDE2_API void WaitForJobCounter(TJobCounter& counter) override;

			/*!
				\brief The method allows to execute some code from main thread nomatter from which thread it's called

				\param[in] action A function that should be executed in the main thread

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE ExecuteInMainThread(const std::function<void()>& action = nullptr) override;

			/*!
				\brief The method unrolls main thread's queue of actions that should be executed only in the main thread
			*/

			TDE2_API void ProcessMainThreadQueue() override;

			/*!
				\brief The method returns a type of the subsystem

				\return A type, which is represented with E_ENGINE_SUBSYSTEM_TYPE's value
			*/

			TDE2_API E_ENGINE_SUBSYSTEM_TYPE GetType() const override;

			TDE2_API static bool IsMainThread();
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS_NO_DCTR(CBaseJobManager)
			virtual ~CBaseJobManager();

			TDE2_API E_RESULT_CODE _onFreeInternal() override;
		protected:
			static constexpr U8     mUpdateTickRate = 60; // \note Single update every 60 frames

			std::atomic_uint8_t     mUpdateCounter;

			TCallbacksQueue         mMainThreadCallbacksQueue;
			mutable std::mutex      mMainThreadCallbacksQueueMutex;

			std::unique_ptr<marl::Scheduler> mpScheduler;

			std::vector<std::unique_ptr<marl::WaitGroup>> mpWaitCountersPool;
			std::atomic<USIZE>                            mNextFreeCounterIndex;
	};
}
