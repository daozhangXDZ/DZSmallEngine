#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


RHIBlendStateRef D3D11DynamicRHI::CreateBlendState()
{
	RHID3D11BlendStateRef blendStateParam = new RHID3D11BlendState();
	HRESULT hr;
	D3D11_RENDER_TARGET_BLEND_DESC rtbd = { 0 };
	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	rtbd.DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC blendDesc = { 0 };
	blendDesc.RenderTarget[0] = rtbd;

	hr = this->md3d11Device->CreateBlendState(&blendDesc, 
		(ID3D11BlendState**)blendStateParam->GetStateNativeAddress());
	COM_ERROR_IF_FAILED(hr, "Failed to create blend state.");
	return blendStateParam;
}


RHIDepthStencilStateRef D3D11DynamicRHI::CreateDepthStencilState()
{
	RHID3D11DepthStencilStateRef DepthStateParam = new RHID3D11DepthStencilState();
	HRESULT hr;
	CD3D11_DEPTH_STENCIL_DESC depthstencildesc(D3D11_DEFAULT);
	depthstencildesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;

	hr = this->md3d11Device->CreateDepthStencilState(&depthstencildesc, 
		(ID3D11DepthStencilState**)DepthStateParam->GetStateNativeAddress());
	COM_ERROR_IF_FAILED(hr, "Failed to create depth stencil state.");
	return DepthStateParam;
}


RHIRasterizerStateRef D3D11DynamicRHI::CreaRasterizerState()
{
	RHID3D11RasterizerStateRef rasterStateParam = new RHID3D11RasterizerState();
	HRESULT hr;
	CD3D11_RASTERIZER_DESC rasterizerDesc(D3D11_DEFAULT);
	hr = this->md3d11Device->CreateRasterizerState(&rasterizerDesc, 
		(ID3D11RasterizerState**)rasterStateParam->GetStateNativeAddress());
	COM_ERROR_IF_FAILED(hr, "Failed to create rasterizer state.");
	return rasterStateParam;
}


void D3D11DynamicRHI::SetRasterizerState(RHIRasterizerStateParamRef rasterizerStateParam)
{
	RHID3D11RasterizerStateRef D3DRasterizerStateParam = static_cast<RHID3D11RasterizerStateRef>(rasterizerStateParam);
	this->md3d11DeviceContext->RSSetState((ID3D11RasterizerState*)D3DRasterizerStateParam->GetStateAddress());
}


void D3D11DynamicRHI::SetDepthState(RHIDepthStencilStateParamRef depthStateParam)
{
	RHID3D11DepthStencilStateRef D3DdepthStateParam = static_cast<RHID3D11DepthStencilStateRef>(depthStateParam);
	this->md3d11DeviceContext->OMSetDepthStencilState((ID3D11DepthStencilState*)D3DdepthStateParam->GetStateAddress(),0);
}


void D3D11DynamicRHI::SetBlendState(RHIBlendStateParamRef blendStateParam)
{
	RHID3D11BlendStateRef D3DblendStateParam = static_cast<RHID3D11BlendStateRef>(blendStateParam);
	this->md3d11DeviceContext->OMSetBlendState((ID3D11BlendState*)D3DblendStateParam->GetStateAddress(), NULL, 0xFFFFFFFF);

}

