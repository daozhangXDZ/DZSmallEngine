#include "RHIGlobalUniform.h"
#include "RHICommandList.h"
#include "RHIUtil.h"

void RHIGlobalUniform::Init()
{


#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
	std::wstring  shaderfolder = L"..\\x64\\Debug\\Shaders\\";
#else  //x86 (Win32)
	std::wstring  shaderfolder = L"..\\Debug\\Shaders\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
	std::wstring  shaderfolder = L"..\\x64\\Release\\Shaders\\";
#else  //x86 (Win32)
	std::wstring  shaderfolder = L"..\\Release\\Shaders\\";
#endif
#endif
	mDefaultVertexShader = RHICreateVertexShader(shaderfolder + L"Default_VS.cso");
	mDefaultPixelShader = RHICreatePixelShader(shaderfolder + L"Default_PS.cso");

	mDefaultInputElement = RHICreateRHIInputElement(VertexPosNormalTangentTex::inputLayout
		, ARRAYSIZE(VertexPosNormalTangentTex::inputLayout));

	mDefualtInputLayout = RHICreateInputLayout(mDefaultInputElement, mDefaultVertexShader);

	//创建基础缓冲区


	mCBDraw = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesEveryDrawing));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBDraw, 0);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBDraw, 0);

	mCBStates = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBDrawingStates));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBStates, 1);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBStates, 1);

	//vFrameCSB = new CBChangesEveryFrame();
	mCBFrame = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesEveryFrame));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBFrame, 2);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBFrame, 2);

	//vResizeCSB = new CBChangesOnResize();
	mCBOnResize = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesOnResize));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBOnResize, 3);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBOnResize, 3);

	mCBRarely = RHICreateUniFormBuffer(nullptr, RHIUtil::CreateLayout(new CBChangesRarely()));
	RHISetUniFormBuffer(mDefaultVertexShader, mCBRarely, 4);
	RHISetUniFormBuffer(mDefaultPixelShader, mCBRarely, 4);
}

void RHIGlobalUniform::Clear()
{
}


RHIUniFormBufferRef RHIGlobalUniform::GetRHIStatesBuffer()
{
	return mCBStates;
}
RHIUniFormBufferRef RHIGlobalUniform::GetRHIFrameBuffer()
{
	return mCBFrame;
}
RHIUniFormBufferRef RHIGlobalUniform::GetRHIResizeBuffer()
{
	return mCBOnResize;
}
RHIUniFormBufferRef RHIGlobalUniform::GetRHIRarelyBuffer()
{
	return mCBRarely;
}
RHIUniFormBufferRef RHIGlobalUniform::GetRHIDrawBuffer()
{
	return mCBDraw;
}