#include "../../include/systems/UI/CPauseMenuLogicSystem.h"
#include "../../include/Components.h"
#include "../../include/Utilities.h"


using namespace TDEngine2;


namespace Game
{
	CPauseMenuLogicSystem::CPauseMenuLogicSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CPauseMenuLogicSystem::Init(const TPauseMenuLogicSystemParams& params)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!params.mpGameModesManager || !params.mpEventManager || !params.mpSceneManager)
		{
			return RC_INVALID_ARGS;
		}

		mpGameModesManager = params.mpGameModesManager;
		mpEventManager = params.mpEventManager;
		mpSceneManager = params.mpSceneManager;

		mIsInitialized = true;

		return RC_OK;
	}

	void CPauseMenuLogicSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<Game::CPauseMenuPanel>();
	}


	static void ProcessPauseMenuInput(IWorld* pWorld, CPauseMenuPanel* pMenuPanel, TPtr<IEventManager> pEventManager)
	{
		/// \note Resume button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mResumeButtonEntityId.Get(), [pEventManager]
		{
			TResumeToGameEvent resumeToGameEvent;
			pEventManager->Notify(&resumeToGameEvent);
		}))
		{
			return;
		}

		/// \note Settings button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mRestartButtonEntityId.Get(), [pEventManager]
		{
			TRestartLevelEvent restartLevelEvent;
			pEventManager->Notify(&restartLevelEvent);
		}))
		{
			return;
		}

		/// \note Quit button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mExitToMenuButtonEntityId.Get(), [pEventManager]
		{
			TLoadMainMenuEvent goToMainMenuEvent;
			pEventManager->Notify(&goToMainMenuEvent);
		}))
		{
			return;
		}
	}


	void CPauseMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<CPauseMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			ProcessPauseMenuInput(pWorld, panels[i], mpEventManager);
		}
	}


	TDE2_API ISystem* CreatePauseMenuLogicSystem(const TPauseMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPauseMenuLogicSystem, result, params);
	}
}