#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include "ViewPortDesc.h"
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")



//////////////////////////////////Shader·ÖÅä////////////////////////////////////////
RHIVertexShaderRef D3D11DynamicRHI::CreateVertexShader(FWString shaderFileName)
{
	RHID3D11VertexShaderRef shaderRes = new RHID3D11VertexShader();
	////////////////////////////////////---InitBuffer---//////////////////////////////////////
	HRESULT hr = D3DReadFileToBlob(shaderFileName.c_str(), (ID3DBlob**)shaderRes->GetResBlobNativeAddressOf());
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderFileName;
		ErrorLogger::Log(hr, errorMsg);
	}
	////////////////////////////////////---Create ShaderByBuffer---//////////////////////////////////////
	//_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//_In_  SIZE_T BytecodeLength,
	//_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//_COM_Outptr_opt_  ID3D11VertexShader **ppVertexShader
	ID3DBlob* bu = (ID3DBlob*)(shaderRes->GetResBlob());
	ID3D11VertexShader** buSha = (ID3D11VertexShader**)(shaderRes->GetNativeAddress());
	md3d11Device->CreateVertexShader(
		bu->GetBufferPointer(),
		bu->GetBufferSize(),
		NULL,
		buSha
	);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to create vertex shader: ";
		errorMsg += shaderFileName;
		ErrorLogger::Log(hr, errorMsg);
	}
	return shaderRes;
}


RHIPixelShaderRef D3D11DynamicRHI::CreatePixelShader(FWString shaderFileName)
{
	RHID3D11PixelShaderRef shaderRes = new RHID3D11PixelShader();
	////////////////////////////////////---InitBuffer---//////////////////////////////////////
	HRESULT hr = D3DReadFileToBlob(shaderFileName.c_str(), (ID3DBlob**)shaderRes->GetResBlobNativeAddressOf());
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to load shader: ";
		errorMsg += shaderFileName;
		ErrorLogger::Log(hr, errorMsg);
	}
	////////////////////////////////////---Create ShaderByBuffer---//////////////////////////////////////
	//_In_reads_(BytecodeLength)  const void *pShaderBytecode,
	//_In_  SIZE_T BytecodeLength,
	//_In_opt_  ID3D11ClassLinkage *pClassLinkage,
	//_COM_Outptr_opt_  ID3D11VertexShader **ppVertexShader
	ID3DBlob* bu = (ID3DBlob*)(shaderRes->GetResBlob());
	ID3D11PixelShader** buSha = (ID3D11PixelShader**)(shaderRes->GetNativeAddress());
	md3d11Device->CreatePixelShader(
		bu->GetBufferPointer(),
		bu->GetBufferSize(),
		NULL,
		buSha
	);
	if (FAILED(hr))
	{
		std::wstring errorMsg = L"Failed to create vertex shader: ";
		errorMsg += shaderFileName;
		ErrorLogger::Log(hr, errorMsg);
	}
	return shaderRes;
}

RHIVertexLayoutRef D3D11DynamicRHI::CreateInputLayout(RHIVertexInputElementParamRef ResTarget, RHIVertexShaderParamRef vertexShader)
{
	RHID3D11VertexShaderRef vD3D11Shader = static_cast<RHID3D11VertexShaderRef>(vertexShader);
	RHID3D11InputLayoutRef vInput = new RHID3D1VertexInputLayout();
	RHIVertexInputElementRef vInputElement = static_cast<RHIVertexInputElementRef>(ResTarget);
	ID3DBlob* bu = (ID3DBlob*)(vD3D11Shader->GetResBlob());

	HRESULT hr = md3d11Device->CreateInputLayout(
		(D3D11_INPUT_ELEMENT_DESC * )vInputElement->elementsDesc,
		vInputElement->elementsNumber,
		bu->GetBufferPointer(),
		bu->GetBufferSize(),
		(ID3D11InputLayout**)vInput->GetNativeAddressOff()
	);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create input layout.");
	}
	return vInput;
}


void D3D11DynamicRHI::OMVSShader(RHIVertexShaderParamRef ResTarget)
{
	RHID3D11VertexShaderRef vD3D11Shader = static_cast<RHID3D11VertexShaderRef>(ResTarget);
	this->md3d11DeviceContext->VSSetShader(vD3D11Shader->GetShader(), NULL, 0);

}


void D3D11DynamicRHI::OMPSShader(RHIPixelShaderParamRef ResTarget)
{
	RHID3D11PixelShaderRef vD3D11Shader = static_cast<RHID3D11PixelShaderRef>(ResTarget);
	this->md3d11DeviceContext->PSSetShader(vD3D11Shader->GetShader(), NULL, 0);
}

void D3D11DynamicRHI::OMPInputLayout(RHIVertexLayoutParamRef ResTarget)
{
	RHID3D11InputLayoutRef vInput = static_cast<RHID3D11InputLayoutRef>(ResTarget);
	this->md3d11DeviceContext->IASetInputLayout((ID3D11InputLayout*)vInput->GetInput());
}


