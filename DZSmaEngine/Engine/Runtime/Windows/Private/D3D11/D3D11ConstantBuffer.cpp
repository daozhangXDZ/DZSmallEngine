#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


 RHIUniFormBufferRef D3D11DynamicRHI::CreateUniFormBuffer(void* Content, UniFormLayout* layout)
{
	 RHID3D11UniFormBufferRef vUniFormBuffer = new RHID3D11UniFormBuffer();
	 D3D11_BUFFER_DESC desc;
	 desc.Usage = D3D11_USAGE_DYNAMIC;
	 desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	 desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	 desc.MiscFlags = 0;
	 desc.ByteWidth = layout->ConstantBufferSize;
	 desc.StructureByteStride = 0;
	 vUniFormBuffer->Layout = layout;

	 HRESULT hr = md3d11Device->CreateBuffer(&desc, 0, vUniFormBuffer->mBuffer.GetAddressOf());
	 COM_ERROR_IF_FAILED(hr, "Failed to CreateConstantBuffer.");
	 return vUniFormBuffer;
}


void  D3D11DynamicRHI::SetUniFormBuffer(RHIVertexShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)
{
	RHID3D11UniFormBufferRef vUniFormBuffer = static_cast<RHID3D11UniFormBuffer*>(ResTarget);
	md3d11DeviceContext->VSSetConstantBuffers(BufferIndex, 1, vUniFormBuffer->mBuffer.GetAddressOf());
	vUniFormBuffer->vertecShader = shader;
	vUniFormBuffer->bindVSIndex = BufferIndex;
	vUniFormBuffer->isBindVS = true;
}

void  D3D11DynamicRHI::SetUniFormBuffer(RHIComputerShader shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)
{
	
}

void  D3D11DynamicRHI::SetUniFormBuffer(RHIPixelShaderRef shader, RHIUniFormBufferParamRef ResTarget, UINT BufferIndex)
{
	RHID3D11UniFormBufferRef vUniFormBuffer = static_cast<RHID3D11UniFormBuffer*>(ResTarget);
	md3d11DeviceContext->PSSetConstantBuffers(BufferIndex, 1, vUniFormBuffer->mBuffer.GetAddressOf());
	vUniFormBuffer->pixelShader = shader;
	vUniFormBuffer->bindPSIndex = BufferIndex;
	vUniFormBuffer->isBindPS = true;
}


void D3D11DynamicRHI::ApplyConstantBuffer(RHIUniFormBufferRef ResTarget, void * pData, bool isReBind)
{
	RHID3D11UniFormBufferRef vUniFormBuffer = static_cast<RHID3D11UniFormBuffer*>(ResTarget);
	D3D11_MAPPED_SUBRESOURCE vSubResource;
	HRESULT hr = md3d11DeviceContext->Map(vUniFormBuffer->mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &vSubResource);
	if (FAILED(hr))
	{
		COM_ERROR_IF_FAILED(hr, "Failed to map constant buffer.");
	}
	CopyMemory(vSubResource.pData, pData, vUniFormBuffer->Layout->ConstantBufferSize);
	this->md3d11DeviceContext->Unmap(vUniFormBuffer->mBuffer.Get(), 0);
	COM_ERROR_IF_FAILED(hr, "Failed to ApplyConstantBuffer.");

	if (isReBind)
	{
		if (vUniFormBuffer->isBindVS)
		{
			SetUniFormBuffer(vUniFormBuffer->vertecShader, ResTarget, vUniFormBuffer->bindVSIndex);
		}
		if (vUniFormBuffer->isBindPS)
		{
			SetUniFormBuffer(vUniFormBuffer->pixelShader, ResTarget, vUniFormBuffer->bindPSIndex);
		}
	}
}
