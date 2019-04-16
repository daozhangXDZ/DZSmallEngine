#pragma once
#include "RHISources.h"

class RHIGlobalUniform
{
private:
	//Ĭ�ϻ�����������Դ
	RHIUniFormBufferRef					mCBStates;
	RHIUniFormBufferRef					mCBFrame;
	RHIUniFormBufferRef					mCBOnResize;
	RHIUniFormBufferRef					mCBRarely;
	RHIUniFormBufferRef					mCBDraw;

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