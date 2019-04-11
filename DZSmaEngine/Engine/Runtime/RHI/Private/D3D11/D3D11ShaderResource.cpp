#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include <WICTextureLoader.h>
using namespace DirectX;

RHIShaderResourceViewRef D3D11DynamicRHI::CreateShaderResourcesView(FWString filePath)
{
	RHID3D11ShaderResViewRef ResTarget = new RHID3D11ShaderResourceView();
	HRESULT hr;
	const WCHAR * vLPPath = filePath.c_str();
	hr = DirectX::CreateWICTextureFromFile(
		md3d11Device.Get(), 
		vLPPath, 
		nullptr, 
		ResTarget->mShaderResView.GetAddressOf()
	);
	COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file.");
	return ResTarget;
}



void D3D11DynamicRHI::SetShaderRessourcesView(int stIndex, int num, RHIShaderResourceViewParamRef ResTarget, EPipeLineFlag bindShaderType)
{
	RHID3D11ShaderResViewRef D3DResTarget = static_cast<RHID3D11ShaderResViewRef>(ResTarget);
	switch (bindShaderType)
	{
	case EPipeLineFlag::VertexShader:
	{
		this->md3d11DeviceContext->VSSetShaderResources(
			stIndex, num,
			D3DResTarget->mShaderResView.GetAddressOf());
	}
	break;

	case EPipeLineFlag::PixelShader:
	{
		this->md3d11DeviceContext->PSSetShaderResources(
			stIndex, num,
			D3DResTarget->mShaderResView.GetAddressOf());
	}
	break;
	}
	
}