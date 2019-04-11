#pragma once
#include <vector>
#include "RenderProxy/primitivesceneproxy.h"
#include "ViewPortDesc.h"
#include "RHISources.h"
#include "RHIState.h"
using namespace std;
class SceneRender
{
public:
	
	SceneRender() {}
	virtual void InitRes() {};
	virtual void Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList) {};
	virtual void InitViewPort(RenderViewBoard ViewBoard) {};
	virtual void UpdateViewPort(ViewPortDesc* desc, bool isUpdateProj) {}

public:
	static SceneRender* GetShaderRender();
	
public:


protected:
	virtual void UpdateViewPortViewMat(ViewPortDesc* desc) = 0;

	virtual void UpdateViewPortProjMat(ViewPortDesc* desc) = 0;

protected:


	RHIRenderTargetRef					mDefaultRenderTarget;
	RHIDepthTargetRef					mDefaultDepthRes;
	RHIVertexShaderRef					mDefaultVertexShader;
	RHIPixelShaderRef					mDefaultPixelShader;

	RHIVertexInputElementRef			mDefaultInputElement;
	RHIVertexLayoutRef					mDefualtInputLayout;

	RHIRasterizerStateRef				mDefaultRasState;
	RHIDepthStencilStateRef				mDefaultDepthState;
	RHIBlendStateRef					mDefaultBlendState;
	RHISampleStateRef					mDefaultTextureSampleState;

	//Ĭ�ϻ�����������Դ
	RHIUniFormBufferRef					mCBStates;
	RHIUniFormBufferRef					mCBFrame;
	RHIUniFormBufferRef					mCBOnResize;
	RHIUniFormBufferRef					mCBRarely;
	RHIUniFormBufferRef					mCBDraw;	
};