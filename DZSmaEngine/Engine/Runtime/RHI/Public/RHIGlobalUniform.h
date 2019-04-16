#pragma once
#include "RHISources.h"

class RHIGlobalUniform
{
private:
	//默认缓冲区数据资源
	RHIUniFormBufferRef					mCBStates;
	RHIUniFormBufferRef					mCBFrame;
	RHIUniFormBufferRef					mCBOnResize;
	RHIUniFormBufferRef					mCBRarely;
	RHIUniFormBufferRef					mCBDraw;

	/// <summary>
	/// 默认的顶点着色，
	/// 不存放于全局ShaderMap中，只是为了方便绑定
	/// </summary>
	RHIVertexShaderRef					mDefaultVertexShader;

	/// <summary>
	/// 默认的像素着色，
	/// 不存放于全局ShaderMap中，只是为了方便绑定
	/// </summary>
	RHIPixelShaderRef					mDefaultPixelShader;


	RHIVertexInputElementRef			mDefaultInputElement;

	RHIVertexLayoutRef					mDefualtInputLayout;

public:
	RHIUniFormBufferRef GetRHIStatesBuffer();
	RHIUniFormBufferRef GetRHIFrameBuffer();
	RHIUniFormBufferRef GetRHIResizeBuffer();
	RHIUniFormBufferRef GetRHIRarelyBuffer();
	RHIUniFormBufferRef GetRHIDrawBuffer();
public:
	void Init();
	void Clear();
};