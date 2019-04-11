#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::InitContantBuffer()
{
	mCBDraw = new D3D11ConstanBufferRes();
	CreateConstantBuffer(mCBDraw, sizeof(CBChangesEveryDrawing));
	BindConstantBuffer(mCBDraw, 0, D3D11ShaderType::VertexShader);
	BindConstantBuffer(mCBDraw, 0, D3D11ShaderType::PixelShader);

	mCBStates = new D3D11ConstanBufferRes();
	CreateConstantBuffer(mCBStates, sizeof(CBDrawingStates));
	BindConstantBuffer(mCBStates, 1, D3D11ShaderType::VertexShader);
	BindConstantBuffer(mCBStates, 1, D3D11ShaderType::PixelShader);

	mCBFrame = new D3D11ConstanBufferRes();
	CreateConstantBuffer(mCBFrame, sizeof(CBChangesEveryFrame));
	BindConstantBuffer(mCBFrame, 2, D3D11ShaderType::VertexShader);
	BindConstantBuffer(mCBFrame, 2, D3D11ShaderType::PixelShader);

	mCBOnResize = new D3D11ConstanBufferRes();
	CreateConstantBuffer(mCBOnResize, sizeof(CBChangesOnResize));
	BindConstantBuffer(mCBOnResize, 3, D3D11ShaderType::VertexShader);

	mCBRarely = new D3D11ConstanBufferRes();
	CreateConstantBuffer(mCBRarely, sizeof(CBChangesRarely));
	BindConstantBuffer(mCBRarely, 4, D3D11ShaderType::VertexShader);
	BindConstantBuffer(mCBRarely, 4, D3D11ShaderType::PixelShader);
}

void D3D11DynamicRHI::CreateConstantBuffer(D3D11ConstanBufferResParamRef ResTarget, UINT pDataWidth)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.ByteWidth = static_cast<UINT>(pDataWidth + (16 - (pDataWidth % 16)));
	desc.StructureByteStride = 0;

	HRESULT hr = md3d11Device->CreateBuffer(&desc, 0, ResTarget->mBuffer.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to CreateConstantBuffer.");
}

void D3D11DynamicRHI::BindConstantBuffer(D3D11ConstanBufferResParamRef ResTarget, UINT index,D3D11ShaderType bindShaderType)
{
	switch (bindShaderType)
	{
	case D3D11ShaderType::VertexShader:
		md3d11DeviceContext->VSSetConstantBuffers(index, 1, ResTarget->mBuffer.GetAddressOf());
		ResTarget->bindVSIndex = index;
		ResTarget->isBindVS = true;
		break;
	case D3D11ShaderType::PixelShader:
		md3d11DeviceContext->PSSetConstantBuffers(index, 1, ResTarget->mBuffer.GetAddressOf());
		ResTarget->bindPSIndex = index;
		ResTarget->isBindPS = true;
		break;
	default:
		break;
	}
}

void D3D11DynamicRHI::ApplyConstantBuffer(D3D11ConstanBufferResParamRef ResTarget,UINT pDataWidth,void * pData,bool isReBind)
{
	D3D11_MAPPED_SUBRESOURCE vSubResource;
	HRESULT hr = md3d11DeviceContext->Map(ResTarget->mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &vSubResource);
	if (FAILED(hr))
	{
		COM_ERROR_IF_FAILED(hr, "Failed to map constant buffer.");
	}
	CopyMemory(vSubResource.pData, pData, pDataWidth);
	this->md3d11DeviceContext->Unmap(ResTarget->mBuffer.Get(), 0);
	COM_ERROR_IF_FAILED(hr, "Failed to ApplyConstantBuffer.");

	if (isReBind)
	{
		if (ResTarget->isBindVS)
		{
			BindConstantBuffer(ResTarget, ResTarget->bindVSIndex, D3D11ShaderType::VertexShader);
		}
		if (ResTarget->isBindPS)
		{
			BindConstantBuffer(ResTarget, ResTarget->bindPSIndex, D3D11ShaderType::PixelShader);
		}
	}
}
