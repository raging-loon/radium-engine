#include "graphics/interface/Adapter.h"
#include "core/debug/Log.h"
#include <Windows.h>
#include <dxgi.h>
#include <wrl/client.h>

#pragma comment(lib, "dxgi.lib")

using radium::AdapterList;

int AdapterList::detectAdapters()
{
	if (!m_gAdapterMap.empty())
	{
		RAD_ENGINE_WARN("[AdapterList] Overwriting existing graphics adapter entries");
		m_gAdapterMap.clear();
	}
	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory;
	HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(hr))
	{
		RAD_ENGINE_INFO("Failed to detect graphics adapters: could not create DxgiFactory1");
		return -1;
	}
	unsigned int i = 0;
	IDXGIAdapter* dev = nullptr;
	while (dxgiFactory->EnumAdapters(i, &dev) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_ADAPTER_DESC desc;
		dev->GetDesc(&desc);
		char convertedName[128];
		memset(convertedName, 0, sizeof(convertedName));
		wcstombs(convertedName, desc.Description, 128);
		RAD_ENGINE_INFO("Found device: {}", convertedName);

		m_gAdapterMap.push_back(convertedName );
		i++;
	}

	return i;
}

int AdapterList::detectDisplays()
{
	if (!m_monitorMap.empty())
	{
		RAD_ENGINE_WARN("[AdapterList] Overwriting existing display entries");
		m_monitorMap.clear();
	}
	DISPLAY_DEVICE dev;
	ZeroMemory(&dev, sizeof(dev));

	dev.cb = sizeof(DISPLAY_DEVICE);
	int index = 0;
	
	while (EnumDisplayDevices(nullptr, index, &dev, 0))
	{
		if (dev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
		{
			RAD_ENGINE_INFO("Found display: {}", dev.DeviceName);
			m_monitorMap.push_back(dev.DeviceName);
		}
		index++;
	}

	return m_monitorMap.size();
}



bool AdapterList::isValidAdapter(unsigned int id)
{
	return id <= m_gAdapterMap.size();
}
