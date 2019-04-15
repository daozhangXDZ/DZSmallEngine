#pragma once
#include <vector>
#include "RenderProxy/primitivesceneproxy.h"
#include "ViewPortDesc.h"
#include "RHISources.h"
#include "RHIState.h"
#include <map>
using namespace std;
class SceneRender
{
public:
	
	SceneRender() {}
	virtual void InitRes() =0;
	virtual void Render(std::vector<PrimitiveSceneProxy*>* RenderProxyList)=0;
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
	
	/// <summary>
	/// Ĭ�ϵĶ�����ɫ��
	/// �������ȫ��ShaderMap�У�ֻ��Ϊ�˷����
	/// </summary>
	RHIVertexShaderRef					mDefaultVertexShader;	
	
	/// <summary>
	/// Ĭ�ϵ�������ɫ��
	/// �������ȫ��ShaderMap�У�ֻ��Ϊ�˷����
	/// </summary>
	RHIPixelShaderRef					mDefaultPixelShader;

	std::map< string, int>				mVertexShaderMap;
	std::map< string, int>				mPixelShadeMap;
	std::vector<RHIVertexShaderRef>     mCurrMaterias_VertexShaderList;
	std::vector<RHIPixelShaderRef>		mCurrMaterias_PixelShaderList;

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