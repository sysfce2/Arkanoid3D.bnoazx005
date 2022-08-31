#include "../../include/components/CPaddle.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CPaddle::CPaddle() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CPaddle::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CPaddle::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CPaddle::GetTypeId()));
			pWriter->SetFloat("speed", mSpeed);

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CPaddle::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Paddle", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CPaddle& component = dynamic_cast<CPaddle&>(editorContext.mComponent);

			/// \note Speed of the paddle
			{
				F32 speed = component.mSpeed;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Speed:");
				imguiContext.FloatField("##Speed", speed, [&component, &speed]() { component.mSpeed = speed; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreatePaddle(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CPaddle, result);
	}


	/*!
		\brief CPaddleFactory's definition
	*/

	CPaddleFactory::CPaddleFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CPaddleFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreatePaddle(result);
	}

	E_RESULT_CODE CPaddleFactory::SetupComponent(CPaddle* pComponent, const TPaddleParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		pComponent->mSpeed = params.mSpeed;

		return RC_OK;
	}


	IComponentFactory* CreatePaddleFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CPaddleFactory, result);
	}
}