#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

RHISampleStateRef D3D11DynamicRHI::CreaTextureSampleState()
{
	RHID3D11SampleStateRef SampleState = new RHID3D11SampleState();
	HRESULT hr;
	CD3D11_SAMPLER_DESC sampDesc(D3D11_DEFAULT);
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = this->md3d11Device->CreateSamplerState(&sampDesc, 
		(ID3D11SamplerState**)SampleState->GetStateNativeAddress()); //Create sampler state
	COM_ERROR_IF_FAILED(hr, "Failed to create sampler state.");
	return SampleState;
}

void D3D11DynamicRHI::SetTextureSample(RHISampleStateParamRef TextureSamParam)
{
	RHID3D11SampleStateRef SampleState = static_cast<RHID3D11SampleStateRef>(TextureSamParam);
	ID3D11SamplerState**  pstate = (ID3D11SamplerState**)SampleState->GetStateNativeAddress();
	this->md3d11DeviceContext->PSSetSamplers(0, 1, 
		pstate);
}
