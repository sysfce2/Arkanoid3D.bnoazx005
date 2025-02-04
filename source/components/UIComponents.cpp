#include "../../include/components/UIComponents.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	/*!
		CMainMenuPanel's definition
	*/

	struct TMainMenuPanelArchiveKeys
	{
		static const std::string mPlayButtonEntityIdKey;
		static const std::string mSettingsButtonEntityIdKey;
		static const std::string mCreditsButtonEntityIdKey;
		static const std::string mQuitButtonEntityIdKey;
	};

	const std::string TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey = "play_button_entity_id";
	const std::string TMainMenuPanelArchiveKeys::mSettingsButtonEntityIdKey = "settings_button_entity_id";
	const std::string TMainMenuPanelArchiveKeys::mCreditsButtonEntityIdKey = "credits_button_entity_id";
	const std::string TMainMenuPanelArchiveKeys::mQuitButtonEntityIdKey = "quit_button_entity_id";


	CMainMenuPanel::CMainMenuPanel() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CMainMenuPanel::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}
		
		mPlayButtonEntityId = LoadEntityRef(pReader, TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey);
		mSettingsButtonEntityId = LoadEntityRef(pReader, TMainMenuPanelArchiveKeys::mSettingsButtonEntityIdKey);
		mCreditsButtonEntityId = LoadEntityRef(pReader, TMainMenuPanelArchiveKeys::mCreditsButtonEntityIdKey);
		mQuitButtonEntityId = LoadEntityRef(pReader, TMainMenuPanelArchiveKeys::mQuitButtonEntityIdKey);

		return RC_OK;
	}

	E_RESULT_CODE CMainMenuPanel::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CMainMenuPanel::GetTypeId()));
			
			SaveEntityRef(pWriter, TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey, mPlayButtonEntityId);
			SaveEntityRef(pWriter, TMainMenuPanelArchiveKeys::mSettingsButtonEntityIdKey, mSettingsButtonEntityId);
			SaveEntityRef(pWriter, TMainMenuPanelArchiveKeys::mCreditsButtonEntityIdKey, mCreditsButtonEntityId);
			SaveEntityRef(pWriter, TMainMenuPanelArchiveKeys::mQuitButtonEntityIdKey, mQuitButtonEntityId);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CMainMenuPanel::PostLoad(CEntityManager* pEntityManager, const TEntitiesMapper& entitiesIdentifiersRemapper)
	{
		mPlayButtonEntityId.SetEntityManager(pEntityManager);
		mSettingsButtonEntityId.SetEntityManager(pEntityManager);
		mCreditsButtonEntityId.SetEntityManager(pEntityManager);
		mQuitButtonEntityId.SetEntityManager(pEntityManager);

		return CBaseComponent::PostLoad(pEntityManager, entitiesIdentifiersRemapper);
	}

	E_RESULT_CODE CMainMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (CMainMenuPanel* pObject = dynamic_cast<CMainMenuPanel*>(pDestObject))
		{
			pObject->mPlayButtonEntityId = mPlayButtonEntityId;
			pObject->mSettingsButtonEntityId = mSettingsButtonEntityId;
			pObject->mCreditsButtonEntityId = mCreditsButtonEntityId;
			pObject->mQuitButtonEntityId = mQuitButtonEntityId;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CMainMenuPanel::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("MainMenuPanel", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CMainMenuPanel& component = dynamic_cast<CMainMenuPanel&>(editorContext.mComponent);

			/// play button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Play Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld), 
					Wrench::StringUtils::GetEmptyStr(), 
					component.mPlayButtonEntityId);

				imguiContext.EndHorizontal();
			}

			/// settings button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Settings Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mSettingsButtonEntityId);

				imguiContext.EndHorizontal();
			}

			/// Credits button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Credits Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mCreditsButtonEntityId);

				imguiContext.EndHorizontal();
			}

			/// Quit button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Quit Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mQuitButtonEntityId);

				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateMainMenuPanel(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CMainMenuPanel, result);
	}


	/*!
		\brief CMainMenuPanelFactory's definition
	*/

	CMainMenuPanelFactory::CMainMenuPanelFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CMainMenuPanelFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateMainMenuPanel(result);
	}

	E_RESULT_CODE CMainMenuPanelFactory::SetupComponent(CMainMenuPanel* pComponent, const TMainMenuPanelParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateMainMenuPanelFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CMainMenuPanelFactory, result);
	}


	/*!
		CPauseMenuPanel's definition
	*/

	struct TPauseMenuPanelArchiveKeys
	{
		static const std::string mResumeButtonEntityIdKey;
		static const std::string mRestartButtonEntityIdKey;
		static const std::string mExitToMenuButtonEntityIdKey;
	};

	const std::string TPauseMenuPanelArchiveKeys::mResumeButtonEntityIdKey = "resume_button_entity_id";
	const std::string TPauseMenuPanelArchiveKeys::mRestartButtonEntityIdKey = "restart_button_entity_id";
	const std::string TPauseMenuPanelArchiveKeys::mExitToMenuButtonEntityIdKey = "exit2menu_button_entity_id";


	CPauseMenuPanel::CPauseMenuPanel() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CPauseMenuPanel::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mResumeButtonEntityId = LoadEntityRef(pReader, TPauseMenuPanelArchiveKeys::mResumeButtonEntityIdKey);
		mRestartButtonEntityId = LoadEntityRef(pReader, TPauseMenuPanelArchiveKeys::mRestartButtonEntityIdKey);
		mExitToMenuButtonEntityId = LoadEntityRef(pReader, TPauseMenuPanelArchiveKeys::mExitToMenuButtonEntityIdKey);
		
		return RC_OK;
	}

	E_RESULT_CODE CPauseMenuPanel::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CPauseMenuPanel::GetTypeId()));

			SaveEntityRef(pWriter, TPauseMenuPanelArchiveKeys::mResumeButtonEntityIdKey, mResumeButtonEntityId);
			SaveEntityRef(pWriter, TPauseMenuPanelArchiveKeys::mRestartButtonEntityIdKey, mRestartButtonEntityId);
			SaveEntityRef(pWriter, TPauseMenuPanelArchiveKeys::mExitToMenuButtonEntityIdKey, mExitToMenuButtonEntityId);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CPauseMenuPanel::PostLoad(CEntityManager* pEntityManager, const TEntitiesMapper& entitiesIdentifiersRemapper)
	{
		mResumeButtonEntityId.SetEntityManager(pEntityManager);
		mRestartButtonEntityId.SetEntityManager(pEntityManager);
		mExitToMenuButtonEntityId.SetEntityManager(pEntityManager);

		return CBaseComponent::PostLoad(pEntityManager, entitiesIdentifiersRemapper);
	}

	E_RESULT_CODE CPauseMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (CPauseMenuPanel* pObject = dynamic_cast<CPauseMenuPanel*>(pDestObject))
		{
			pObject->mResumeButtonEntityId = mResumeButtonEntityId;
			pObject->mRestartButtonEntityId = mRestartButtonEntityId;
			pObject->mExitToMenuButtonEntityId = mExitToMenuButtonEntityId;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CPauseMenuPanel::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("PauseMenuPanel", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CPauseMenuPanel& component = dynamic_cast<CPauseMenuPanel&>(editorContext.mComponent);

			/// play button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Resume Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mResumeButtonEntityId);

				imguiContext.EndHorizontal();
			}

			/// settings button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Restart Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mRestartButtonEntityId);

				imguiContext.EndHorizontal();
			}

			/// Credits button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Exit Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mExitToMenuButtonEntityId);

				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreatePauseMenuPanel(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CPauseMenuPanel, result);
	}


	/*!
		\brief CPauseMenuPanelFactory's definition
	*/

	CPauseMenuPanelFactory::CPauseMenuPanelFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CPauseMenuPanelFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreatePauseMenuPanel(result);
	}

	E_RESULT_CODE CPauseMenuPanelFactory::SetupComponent(CPauseMenuPanel* pComponent, const TPauseMenuPanelParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreatePauseMenuPanelFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CPauseMenuPanelFactory, result);
	}


	/*!
		COptionsMenuPanel's definition
	*/

	struct TOptionsMenuPanelArchiveKeys
	{
		static const std::string mBackButtonEntityIdKey;
	};

	const std::string TOptionsMenuPanelArchiveKeys::mBackButtonEntityIdKey = "back_button_entity_id";


	COptionsMenuPanel::COptionsMenuPanel() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE COptionsMenuPanel::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mBackButtonEntityId = LoadEntityRef(pReader, TOptionsMenuPanelArchiveKeys::mBackButtonEntityIdKey);

		return RC_OK;
	}

	E_RESULT_CODE COptionsMenuPanel::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(COptionsMenuPanel::GetTypeId()));

			SaveEntityRef(pWriter, TOptionsMenuPanelArchiveKeys::mBackButtonEntityIdKey, mBackButtonEntityId);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE COptionsMenuPanel::PostLoad(CEntityManager* pEntityManager, const TEntitiesMapper& entitiesIdentifiersRemapper)
	{
		mBackButtonEntityId.SetEntityManager(pEntityManager);

		return CBaseComponent::PostLoad(pEntityManager, entitiesIdentifiersRemapper);
	}

	E_RESULT_CODE COptionsMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (COptionsMenuPanel* pObject = dynamic_cast<COptionsMenuPanel*>(pDestObject))
		{
			pObject->mBackButtonEntityId = mBackButtonEntityId;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void COptionsMenuPanel::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("OptionsMenuPanel", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			COptionsMenuPanel& component = dynamic_cast<COptionsMenuPanel&>(editorContext.mComponent);

			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Back Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mBackButtonEntityId);

				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateOptionsMenuPanel(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, COptionsMenuPanel, result);
	}


	/*!
		\brief COptionsMenuPanelFactory's definition
	*/

	COptionsMenuPanelFactory::COptionsMenuPanelFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* COptionsMenuPanelFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateOptionsMenuPanel(result);
	}

	E_RESULT_CODE COptionsMenuPanelFactory::SetupComponent(COptionsMenuPanel* pComponent, const TOptionsMenuPanelParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateOptionsMenuPanelFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, COptionsMenuPanelFactory, result);
	}


	/*!
		CCreditsMenuPanel's definition
	*/

	struct TCreditsMenuPanelArchiveKeys
	{
		static const std::string mBackButtonEntityIdKey;
	};

	const std::string TCreditsMenuPanelArchiveKeys::mBackButtonEntityIdKey = "back_button_entity_id";


	CCreditsMenuPanel::CCreditsMenuPanel() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CCreditsMenuPanel::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mBackButtonEntityId = LoadEntityRef(pReader, TCreditsMenuPanelArchiveKeys::mBackButtonEntityIdKey);

		return RC_OK;
	}

	E_RESULT_CODE CCreditsMenuPanel::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CCreditsMenuPanel::GetTypeId()));

			SaveEntityRef(pWriter, TCreditsMenuPanelArchiveKeys::mBackButtonEntityIdKey, mBackButtonEntityId);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CCreditsMenuPanel::PostLoad(CEntityManager* pEntityManager, const TEntitiesMapper& entitiesIdentifiersRemapper)
	{
		mBackButtonEntityId.SetEntityManager(pEntityManager);

		return CBaseComponent::PostLoad(pEntityManager, entitiesIdentifiersRemapper);
	}

	E_RESULT_CODE CCreditsMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (CCreditsMenuPanel* pObject = dynamic_cast<CCreditsMenuPanel*>(pDestObject))
		{
			pObject->mBackButtonEntityId = mBackButtonEntityId;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CCreditsMenuPanel::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("CreditsMenuPanel", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CCreditsMenuPanel& component = dynamic_cast<CCreditsMenuPanel&>(editorContext.mComponent);

			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Back Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld),
					Wrench::StringUtils::GetEmptyStr(),
					component.mBackButtonEntityId);

				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateCreditsMenuPanel(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CCreditsMenuPanel, result);
	}


	/*!
		\brief CCreditsMenuPanelFactory's definition
	*/

	CCreditsMenuPanelFactory::CCreditsMenuPanelFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CCreditsMenuPanelFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateCreditsMenuPanel(result);
	}

	E_RESULT_CODE CCreditsMenuPanelFactory::SetupComponent(CCreditsMenuPanel* pComponent, const TCreditsMenuPanelParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateCreditsMenuPanelFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CCreditsMenuPanelFactory, result);
	}
}