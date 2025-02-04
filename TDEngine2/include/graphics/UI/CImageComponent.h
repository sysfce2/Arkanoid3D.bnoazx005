/*!
	\file CImageComponent.h
	\date 04.05.2021
	\authors Kasimov Ildar
*/

#pragma once


#include "../../ecs/CBaseComponent.h"
#include "../../math/TVector2.h"
#include "../../math/TRect.h"
#include "../../utils/Color.h"


namespace TDEngine2
{
	enum class TResourceId : U32;


	/*!
		\brief A factory function for creation objects of CImage's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CImage's implementation
	*/

	TDE2_API IComponent* CreateImage(E_RESULT_CODE& result);


	/*!
		class CImage

		\brief The interface describes a functionality of UI element that represents an image. The entity is one of fundamental parts of UI.
	*/

	class CImage : public CBaseComponent, public CPoolMemoryAllocPolicy<CImage, 1 << 20>
	{
		public:
			friend TDE2_API IComponent* CreateImage(E_RESULT_CODE& result);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CImage)

			/*!
				\brief The method deserializes object's state from given reader

				\param[in, out] pReader An input stream of data that contains information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Load(IArchiveReader* pReader) override;

			/*!
				\brief The method serializes object's state into given stream

				\param[in, out] pWriter An output stream of data that writes information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Save(IArchiveWriter* pWriter) override;

			/*!
				\brief The method creates a new deep copy of the instance and returns a smart pointer to it.
				The original state of the object stays the same

				\param[in] pDestObject A valid pointer to an object which the properties will be assigned into
			*/

			TDE2_API E_RESULT_CODE Clone(IComponent*& pDestObject) const override;

			TDE2_API E_RESULT_CODE SetImageId(const std::string& id);
			TDE2_API E_RESULT_CODE SetImageResourceId(TResourceId resourceId);
			
			TDE2_API void SetColor(const TColor32F& value);

			TDE2_API void SetDirtyFlag(bool value);

			TDE2_API const std::string& GetImageId() const;
			TDE2_API TResourceId GetImageResourceId() const;

			TDE2_API const TColor32F& GetColor() const;

			TDE2_API bool IsDirty() const;

			/*!
				\return The method returns type name (lowercase is preffered)
			*/

			TDE2_API const std::string& GetTypeName() const override;

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CImage)
		protected:
			std::string mImageSpriteId;
			TResourceId mImageResourceId;
			TColor32F   mColor;
			bool        mIsDirty;
	};


	/*!
		struct TImageParameters

		\brief The structure contains parameters for creation of CImage
	*/

	typedef struct TImageParameters : public TBaseComponentParameters
	{
	} TImageParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(Image, TImageParameters);
}