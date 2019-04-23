#include "D3D11/D3D11DynamicRHI.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

void D3D11DynamicRHI::SetPrimitiveTology(PrimitiveTopology pDrawType)
{
	D3D11_PRIMITIVE_TOPOLOGY vD3D11DrawType;
	switch (pDrawType)
	{
	case PrimitiveTopology::TRIANGLELIST:
		vD3D11DrawType = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	default:
		vD3D11DrawType = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	}
	this->md3d11DeviceContext->IASetPrimitiveTopology(vD3D11DrawType);
}