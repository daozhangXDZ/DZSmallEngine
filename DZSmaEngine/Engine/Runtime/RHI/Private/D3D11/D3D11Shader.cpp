#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include "ViewPortDesc.h"
#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

void D3D11DynamicRHI::InitShader()
{

	std::wstring shaderfolder = L"";
#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Debug\\Shaders\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Debug\\Shaders\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Release\\Shaders\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Release\\Shaders\\";
#endif
#endif
	}
	mDefaultVertexShader = new D3D11VertexShaderRes();
	mDefaultPixelShader = new D3D11PixelShaderRes();
	CreateVertexShader(mDefaultVertexShader, shaderfolder + L"Basic_VS_3D.cso");
	CreatePixelShader(mDefaultPixelShader, shaderfolder + L"Basic_PS_3D.cso");
	mDefaultInputLayout = new D3D11InputLayoutRes();
	D3DInputElementResParamRef ref = new D3DInputElementRes();
	ref->elementsDesc = const_cast<D3D11_INPUT_ELEMENT_DESC*>(VertexPosNormalTex::inputLayout);
	ref->elementsNumber = ARRAYSIZE(VertexPosNormalTex::inputLayout);
	CreateInputLayout(mDefaultInputLayout, ref, mDefaultVertexShader);
}



//////////////////////////////////Shader·ÖÅä////////////////////////////////////////
void D3D11DynamicRHI::CreateVertexShader(D3D11VertexShaderResParamRef ResTarget, FWString shaderFileName)
{
	////////////////////////////////////---InitBuffer---//////////////////////////////////////
	HRESULT hr = D3DReadFileToBlob(shaderFileName.c_str(), (ID3DBlob**)ResTarget->GetResBlobNativeAddressOf());
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
	ID3DBlob* bu = (ID3DBlob*)(ResTarget->GetResBlob());
	ID3D11VertexShader** buSha = (ID3D11VertexShader**)(ResTarget->GetNativeAddress());
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
}


void D3D11DynamicRHI::CreatePixelShader(D3D11PixelShaderResParamRef ResTarget, FWString shaderFileName)
{
	////////////////////////////////////---InitBuffer---//////////////////////////////////////
	HRESULT hr = D3DReadFileToBlob(shaderFileName.c_str(), (ID3DBlob**)ResTarget->GetResBlobNativeAddressOf());
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
	ID3DBlob* bu = (ID3DBlob*)(ResTarget->GetResBlob());
	ID3D11PixelShader** buSha = (ID3D11PixelShader**)(ResTarget->GetNativeAddress());
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
}

void D3D11DynamicRHI::CreateInputLayout(D3D11InputLayoutRes* outInput,D3DInputElementResParamRef ResTarget, D3D11VertexShaderResParamRef vertexShader)
{
	ID3DBlob* bu = (ID3DBlob*)(vertexShader->GetResBlob());
	HRESULT hr = md3d11Device->CreateInputLayout(ResTarget->elementsDesc, 
		ResTarget->elementsNumber, 
		bu->GetBufferPointer(),
		bu->GetBufferSize(),
		(ID3D11InputLayout**)outInput->GetNativeAddressOff()
	);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Failed to create input layout.");
	}
}


void D3D11DynamicRHI::OMVSShader(D3D11VertexShaderResParamRef ResTarget)
{
	this->md3d11DeviceContext->VSSetShader(ResTarget->GetShader(), NULL, 0);

}


void D3D11DynamicRHI::OMPSShader(D3D11PixelShaderResParamRef ResTarget)
{
	this->md3d11DeviceContext->PSSetShader(ResTarget->GetShader(), NULL, 0);
}

void D3D11DynamicRHI::OMPInputLayout(D3D11InputLayoutResParamRef ResTarget)
{
	this->md3d11DeviceContext->IASetInputLayout((ID3D11InputLayout*)ResTarget->GetInput());
}


void D3D11DynamicRHI::InitDefaultState()
{
	/*D3D11RasterizerStateRes*							mDefaultRasState;
	D3D11DepthStencilStateRes*							mDepthState;
	D3D11BlendStateRes*									mBlendStateRes;*/
	mDefaultRasState = new D3D11RasterizerStateRes();
	mDefaultDepthState = new D3D11DepthStencilStateRes();
	mDefaultBlendState = new D3D11BlendStateRes();
	mDefaultTextureSampleState = new D3D11TextureSampleState();
	this->CreaRasterizerState(mDefaultRasState);
	this->CreateDepthStencilState(mDefaultDepthState);
	this->CreateBlendState(mDefaultBlendState);
	this->CreaTextureSampleState(mDefaultTextureSampleState);
}

