#include "IRenderDriver.h"
#include "core/SmartPtr.h"
#include "core/debug/Log.h"
#ifdef RAD_API_OPENGL
# include "drivers/opengl/oglRenderDriver.h"
#endif // RAD_API_OPENGL

#ifdef RAD_API_DX12
# include "drivers/dx12/dx12RenderDriver.h"
#endif // RAD_API_DX12

#ifdef RAD_API_VULKAN
# include "drivers/vulkan/vkRenderDriver.h"
#endif // RAD_API_VULKAN

using radium::IRenderDriver;
using radium::Ref;


Ref<IRenderDriver> IRenderDriver::createRenderDriver(RenderAPI api)
{
	switch (api)
	{

		case RenderAPI::OPENGL:
		#ifdef RAD_API_OPENGL
			return radium::MakeRef<radium::oglRenderDriver>();
		#else
			RAD_ENGINE_CRITICAL("Config specifies unavailable API (opengl). Please check engine.ini");
			return nullptr;
		#endif RAD_API_OPENGL

		
		case RenderAPI::DIRECTX12:
		#ifdef RAD_API_DX12
			return radium::MakeRef<radium::dx12RenderDriver>();
		#else
			RAD_ENGINE_CRITICAL("Config specifies unavailable API (DirectX 12). Please check engine.ini");
			return nullptr;
		#endif RAD_API_DX12

		
		case RenderAPI::VULKAN:
		#ifdef RAD_API_VULKAN
			return radium::MakeRef<radium::vkRenderDriver>();
		#else
			RAD_ENGINE_CRITICAL("Config specifies unavailable API (Vulkan). Please check engine.ini");
			return nullptr;
		#endif RAD_API_VULKAN

	
		default:
			RAD_ENGINE_CRITICAL("Config specifies unknown graphics API (#{}). Please check engine.ini", (int)api);
			return nullptr;


	}
}
