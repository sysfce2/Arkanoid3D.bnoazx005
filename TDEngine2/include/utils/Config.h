/*!
	\file Config.h
	\date 16.09.2018
	\authors Kasimov Ildar
*/


#pragma once


#include <cstddef>


namespace TDEngine2
{
	#define TDE2_WINDOWS (_WIN32 | _WIN64)

	/// Macroses' definitions to handle exporting objects

	#if TDE2_WINDOWS || defined(_MSC_VER)
		#define TDE2_APIENTRY __cdecl					///< Calling convention for VS

		#if defined(TDE2_DLLIMPORT)
			#define TDE2_API __declspec(dllimport)
		#else
			#define TDE2_API __declspec(dllexport)
		#endif
	#elif defined(__GNUC__)
		#define TDE2_APIENTRY __attribute__((cdecl))	///< Calling convention for GNUC

		#if defined(TDE2_DLLIMPORT)
			#define TDE2_API 
		#else
			#define TDE2_API __attribute__((visibility("default")))
		#endif
	#else /// Unknown platform and compiler
		#define TDE2_API 
	#endif

	/// Platform-specific macroses are used to configure build in compile time
	
	#define TDE2_BUILD_OGL_GCTX_PLUGIN
	#define TDE2_BUILD_YAML_FORMAT_SUPPORT_PLUGIN
	#define TDE2_BUILD_FMOD_CTX_PLUGIN
	#define TDE2_BUILD_BULLET_PHYSICS_PLUGIN

	#if TDE2_WINDOWS
		#define TDE2_USE_WINPLATFORM

		#define TDE2_BUILD_D3D11_GCTX_PLUGIN

	#elif defined(__unix__) || defined(__unix) || defined(unix)
		#define TDE2_USE_UNIXPLATFORM

	#else
	#endif


	#define TDE2_MAJOR_VERSON  0
	#define TDE2_MINOR_VERSION 6
	#define TDE2_PATCH_VERSION 21

	constexpr unsigned int EngineVersion = (TDE2_MAJOR_VERSON << 16) | (TDE2_MINOR_VERSION << 8) | TDE2_PATCH_VERSION;


	#define TDE2_DEBUG_MODE !NDEBUG
	#define TDE2_PRODUCTION_MODE 1

	#define GLEW_NO_GLU ///< Disable GLU 

	/// Main logger's settings
	#define MAIN_LOGGER_FILEPATH "TDEngine2.log"


	/// Math configurable constants
	constexpr float FloatEpsilon = 1e-3f;

	///< Memory manager configuration
	constexpr size_t PerRenderQueueMemoryBlockSize = 1024 * 1024 * 2;  /// 2 MiB

	/// Renderer's configuration
	constexpr unsigned int PreCreatedNumOfVertexBuffers = 5;
	
	constexpr unsigned int SpriteInstanceDataBufferSize = 1024 * 1024 * 4; /// 4 MiB
 
	#define TDE2_EDITORS_ENABLED 1

	#define TDE2_RESOURCES_STREAMING_ENABLED 1
	#define TDE2_MEM_PROFILER_BASE_OBJECT_SAVE_STACKTRACE 0
	#define TDE2_BUILTIN_PERF_PROFILER_ENABLED 0
}
