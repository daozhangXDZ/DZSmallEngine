#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::CreateIndexBuffer(D3D11IndexBufferResParamRef ResTarget, DWORD * pMemData, UINT numIndices)
{
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
}

void D3D11DynamicRHI::BindIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int statIndex, DXGI_FORMAT pformat)
{
	md3d11DeviceContext->IASetIndexBuffer(ResTarget->Get(), pformat, statIndex);
}

void D3D11DynamicRHI::DrawIndexBuffer(D3D11IndexBufferResParamRef ResTarget, int startIndexPos, int startIndexVertex)
{
	md3d11DeviceContext->DrawIndexed(ResTarget->BufferSize(), startIndexPos, startIndexVertex); //Draw
}