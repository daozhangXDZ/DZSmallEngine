#include "D3D11/AdapterReader.h"
#include "LogUtil/ErrorLogger.h"
#include <wrl/client.h>

std::vector<AdapterReaderData> AdapterReader::adapterList;

std::vector<AdapterReaderData> AdapterReader::getAdapters()
{
	if (adapterList.size() > 0)
	{
		return adapterList;
	}

	Microsoft::WRL::ComPtr< IDXGIFactory> pFactory;

	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void **>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create DXGIFactory for enumerating adapters.");
		exit(-1);
	}
	IDXGIAdapter * pAdapter;
	UINT vAdapterID = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(vAdapterID, &pAdapter)))
	{
		adapterList.push_back(AdapterReaderData(pAdapter));
		vAdapterID += 1;
	}
	return adapterList;
}

AdapterReaderData::AdapterReaderData(IDXGIAdapter* pAdapter)
{
	this->mAdapter = pAdapter;
	HRESULT hr = mAdapter->GetDesc(&this->mAdaDesc);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to Get Description for IDXGIAdapter.");
	}
}

AdapterReaderData::~AdapterReaderData()
{
	
}

IDXGIAdapter * AdapterReaderData::getAdapter()
{
	return mAdapter;
}

DXGI_ADAPTER_DESC * AdapterReaderData::getAdapterDesc()
{
	return &mAdaDesc;
}
