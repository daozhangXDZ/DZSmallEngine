#include "D3D11/D3D11DynamicRHI.h"
#include "D3D11/AdapterReader.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include "LogUtil/DXTrace.h"
#include <d2d1.h>
#include <dwrite.h>
#include <d3d11_1.h>
#include <wrl/client.h>

void D3D11DynamicRHI::InitRenderDevice()
{
	HWND hwd = (HWND)GEngineApliation->GetCurrMainHWD();
	int mClientWidth = this->view_width;
	int mClientHeight = this->view_height;
	
	HRESULT hr = S_OK;

	// 创建D3D设备 和 D3D设备上下文
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;	// Direct2D需要支持BGRA格式
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 驱动类型数组
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	// 特性等级数组
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;
	D3D_DRIVER_TYPE d3dDriverType;
	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		d3dDriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, md3d11Device.GetAddressOf(), &featureLevel, md3d11DeviceContext.GetAddressOf());

		if (hr == E_INVALIDARG)
		{
			// Direct3D 11.0 的API不承认D3D_FEATURE_LEVEL_11_1，所以我们需要尝试特性等级11.0以及以下的版本
			hr = D3D11CreateDevice(nullptr, d3dDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, md3d11Device.GetAddressOf(), &featureLevel, md3d11DeviceContext.GetAddressOf());
		}

		if (SUCCEEDED(hr))
			break;
	}

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
	}

	// 检测是否支持特性等级11.0或11.1
	if (featureLevel != D3D_FEATURE_LEVEL_11_0 && featureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
	}

	// 检测 MSAA支持的质量等级
	md3d11Device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_B8G8R8A8_UNORM, 4, &m4xMsaaQuality);	// 注意此处DXGI_FORMAT_B8G8R8A8_UNORM
	assert(m4xMsaaQuality > 0);


	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;	// D3D11.0(包含DXGI1.1)的接口类
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;	// D3D11.1(包含DXGI1.2)特有的接口类

	// 为了正确创建 DXGI交换链，首先我们需要获取创建 D3D设备 的 DXGI工厂，否则会引发报错：
	// "IDXGIFactory::CreateSwapChain: This function is being called with a device from a different IDXGIFactory."
	HR(md3d11Device.As(&dxgiDevice));
	HR(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory1.GetAddressOf())));
	{
		// 填充DXGI_SWAP_CHAIN_DESC用以描述交换链
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = mClientWidth;
		sd.BufferDesc.Height = mClientHeight;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;	// 注意此处DXGI_FORMAT_B8G8R8A8_UNORM
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		// 是否开启4倍多重采样？
		if (mEnable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hwd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;
		HR(dxgiFactory1->CreateSwapChain(md3d11Device.Get(), &sd, mdxgiSwapChain.GetAddressOf()));
	}
	// 可以禁止alt+enter全屏
	dxgiFactory1->MakeWindowAssociation(hwd, DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);
}

