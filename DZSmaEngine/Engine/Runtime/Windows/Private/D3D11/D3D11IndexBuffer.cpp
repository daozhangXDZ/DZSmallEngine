#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

RHIIndexBufferRef D3D11DynamicRHI::CreateIndexBuffer(DWORD * pMemData, UINT numIndices)
{
	RHID3D11IndexBufferRef ResTarget = new RHID3D11IndexBuffer();
	HRESULT hr;
	ResTarget->bufferSize = numIndices;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD)*numIndices;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vSubData;
	vSubData.pSysMem = pMemData;

	hr = md3d11Device->CreateBuffer(&indexBufferDesc, &vSubData, ResTarget->buffer.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to CreateIndexBuffer.");
	return ResTarget;
}

void D3D11DynamicRHI::BindIndexBuffer(RHIIndexBufferParamRef ResTarget, int statIndex, DXGI_FORMAT pformat)
{
	RHID3D11IndexBufferParamRef ResTargetParam = static_cast<RHID3D11IndexBufferParamRef>(ResTarget);
	md3d11DeviceContext->IASetIndexBuffer(ResTargetParam->Get(), pformat, statIndex);
}

void D3D11DynamicRHI::DrawIndexBuffer(RHIIndexBufferParamRef ResTarget, int startIndexPos, int startIndexVertex)
{
	RHID3D11IndexBufferParamRef ResTargetParam = static_cast<RHID3D11IndexBufferParamRef>(ResTarget);
	md3d11DeviceContext->DrawIndexed(ResTargetParam->BufferSize(), startIndexPos, startIndexVertex); //Draw
}