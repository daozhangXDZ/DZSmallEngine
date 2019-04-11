#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

RHIVertexBufferRef D3D11DynamicRHI::CreateVertexBuffer(void*data, UINT descSize, UINT numVertices)
{
	RHID3D11VertexBufferRef ResTarget = new RHID3D11VertexBuffer();
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
	return ResTarget;
}

void D3D11DynamicRHI::BindVertexBuffer(RHIVertexBufferParamRef ResTarget,int statIndex, int Num,UINT offset)
{
	RHID3D11VertexBufferRef ResTargetParam = static_cast<RHID3D11VertexBufferRef>(ResTarget);
	md3d11DeviceContext->IASetVertexBuffers(statIndex, Num, ResTargetParam->GetAddressOf(), ResTargetParam->StridePtr(), &offset);
}