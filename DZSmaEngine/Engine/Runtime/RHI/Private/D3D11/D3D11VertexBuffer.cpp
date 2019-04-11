#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::CreateVertexBuffer(D3D11VertexBufferResParamRef ResTarget, void*data, UINT descSize, UINT numVertices)
{
	if (ResTarget->Get() != nullptr)
		ResTarget->Reset();

	ResTarget->SetBufferSize(numVertices);

	if (ResTarget->StridePtr() == nullptr)
		ResTarget->stride = std::make_shared<UINT>(descSize);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = descSize * numVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = data;

	HRESULT hr = md3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, ResTarget->buffer.GetAddressOf());
	COM_ERROR_IF_FAILED(hr, "Failed to CreateVertexBuffer.");
}

void D3D11DynamicRHI::BindVertexBuffer(D3D11VertexBufferResParamRef ResTarget,int statIndex, int Num,UINT offset)
{
	md3d11DeviceContext->IASetVertexBuffers(statIndex, Num, ResTarget->GetAddressOf(), ResTarget->StridePtr(), &offset);
}