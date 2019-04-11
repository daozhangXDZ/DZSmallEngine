#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include <WICTextureLoader.h>
using namespace DirectX;

void D3D11DynamicRHI::CreateShaderResourcesView(D3D11ShaderResourceViewResParamRef ResTarget, FWString filePath)
{
	HRESULT hr;
	const WCHAR * vLPPath = filePath.c_str();
	hr = DirectX::CreateWICTextureFromFile(
		md3d11Device.Get(), 
		vLPPath, 
		nullptr, 
		ResTarget->mShaderResView.GetAddressOf()
	);
	COM_ERROR_IF_FAILED(hr, "Failed to create wic texture from file.");
}



void D3D11DynamicRHI::SetShaderResourcesView(int stIndex, int num, 
	D3D11ShaderResourceViewResParamRef ResTarget, D3D11ShaderType bindShaderType
)
{
	switch (bindShaderType)
	{
	case D3D11ShaderType::VertexShader:
	{
		this->md3d11DeviceContext->VSSetShaderResources(
			stIndex, num,
			ResTarget->mShaderResView.GetAddressOf());
	}
	break;

	case D3D11ShaderType::PixelShader:
	{
		this->md3d11DeviceContext->PSSetShaderResources(
			stIndex, num,
			ResTarget->mShaderResView.GetAddressOf());
	}
	break;
	}
	
}