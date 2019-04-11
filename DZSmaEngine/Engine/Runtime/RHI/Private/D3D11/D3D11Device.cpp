#include "D3D11/D3D11DynamicRHI.h"
#include "D3D11/AdapterReader.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::InitRenderDevice()
{
	HWND hwd = (HWND)GEngineApliation->GetCurrMainHWD();
	int sizeX = this->view_width;
	int sizeY = this->view_height;
	std::vector<AdapterReaderData> adapters = AdapterReader::getAdapters();

	//if (adapters.size() < 1)
	//{
	//	ErrorLogger::Log("No IDXGI Adapters found.");
	//	return false;
	//}

	///////////////////////////////------------SwapChian------------///////////////////////////////////////////
	DXGI_SWAP_CHAIN_DESC scd = { 0 };

	scd.BufferDesc.Width = sizeX;
	scd.BufferDesc.Height = sizeY;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hwd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr;
	hr = D3D11CreateDeviceAndSwapChain(
		adapters[0].getAdapter(),				//IDXGI Adapter
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,									//FOR SOFTWARE DRIVER TYPE
		NULL,									//FLAGS FOR RUNTIME LAYERS
		NULL,									//FEATURE LEVELS ARRAY
		0,										//# OF FEATURE LEVELS IN ARRAY
		D3D11_SDK_VERSION,
		&scd,									//Swapchain description
		this->mdxgiSwapChain.GetAddressOf(),	//Swapchain Address
		this->md3d11Device.GetAddressOf(),		//Device Address
		NULL,									//Supported feature level
		this->md3d11DeviceContext.GetAddressOf()//Device Context Address
	);
}

