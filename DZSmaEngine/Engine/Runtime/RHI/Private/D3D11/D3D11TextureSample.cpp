#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::CreaTextureSampleState(D3D11TextureSampleStateParamRef TextureSamParam)
{
	HRESULT hr;
	CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = this->md3d11Device->CreateSamplerState(&sampDesc, 
		(ID3D11SamplerState**)TextureSamParam->GetStateNativeAddress()); //Create sampler state
	COM_ERROR_IF_FAILED(hr, "Failed to create sampler state.");
}

void D3D11DynamicRHI::SetTextureSample(D3D11TextureSampleStateParamRef TextureSamParam)
{
	ID3D11SamplerState**  pstate = (ID3D11SamplerState**)TextureSamParam->GetStateNativeAddress();
	this->md3d11DeviceContext->PSSetSamplers(0, 1, 
		pstate);
}
