#pragma once
#include <vector> 
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"DXGI.lib")

class AdapterReaderData
{
public:
	AdapterReaderData() = delete;
	AdapterReaderData(IDXGIAdapter* pAdapter);
	~AdapterReaderData();

public:
	IDXGIAdapter* getAdapter();
	DXGI_ADAPTER_DESC* getAdapterDesc();

private:
	IDXGIAdapter* mAdapter = nullptr;
	DXGI_ADAPTER_DESC mAdaDesc;
};

class AdapterReader
{
public:
	static std::vector< AdapterReaderData> getAdapters();
private:
	static std::vector< AdapterReaderData> adapterList;
};