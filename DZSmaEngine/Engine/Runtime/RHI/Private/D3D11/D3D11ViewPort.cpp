#include "D3D11/D3D11DynamicRHI.h"
#include "d3d11.h"
#include "EngineGlobal.h"
#include "D3D11/AdapterReader.h"
void D3D11DynamicRHI::OMViewPort(float view_width,float  view_height)
{
	CD3D11_VIEWPORT viewport(0.0f, 0.0f, 
		static_cast<float>(view_width), 
		static_cast<float>(view_height));
	this->md3d11DeviceContext->RSSetViewports(1, &viewport);	
}



void D3D11DynamicRHI::Present()
{
	this->mdxgiSwapChain->Present(0, NULL);
}