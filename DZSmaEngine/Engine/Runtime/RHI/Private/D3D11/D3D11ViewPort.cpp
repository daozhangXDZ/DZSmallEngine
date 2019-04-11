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

void D3D11DynamicRHI::InitializeViewPort()
{
	CBChangesOnResize vResizeCSB;
	vResizeCSB.proj = mViewPortDesc.ProjMat;
	CBChangesEveryFrame vFrameCSB;
	vFrameCSB.view = mViewPortDesc.viewMat;
	ApplyConstantBuffer(mCBOnResize, sizeof(CBChangesOnResize), &vResizeCSB, true);
	ApplyConstantBuffer(mCBFrame, sizeof(CBChangesEveryFrame), &vFrameCSB, true);
	OMViewPort(this->view_width, this->view_height);
}

void D3D11DynamicRHI::UpdateViewPort(ViewPortDesc* desc)
{
	/*if (mViewPortDesc.ProjMat desc->ProjMat)*/
	UpdateViewPortViewMat(desc);
	UpdateViewPortProjMat(desc);
}


void D3D11DynamicRHI::UpdateViewPortViewMat(ViewPortDesc* desc)
{

	{
		mViewPortDesc.viewMat = desc->viewMat;
		CBChangesEveryFrame vFrameCSB;
		vFrameCSB.view = XMMatrixTranspose(mViewPortDesc.viewMat);
		ApplyConstantBuffer(mCBFrame, sizeof(CBChangesEveryFrame), &vFrameCSB, true);
	}
}

void D3D11DynamicRHI::UpdateViewPortProjMat(ViewPortDesc* desc)
{
	{
		mViewPortDesc.ProjMat = desc->ProjMat;
		CBChangesOnResize vResizeCSB;
		vResizeCSB.proj = XMMatrixTranspose(mViewPortDesc.ProjMat);
		ApplyConstantBuffer(mCBOnResize, sizeof(CBChangesOnResize), &vResizeCSB, true);
	}
}


void D3D11DynamicRHI::Present()
{
	this->mdxgiSwapChain->Present(0, NULL);
}