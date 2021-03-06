#pragma once
#include "ShaderUtils.h"

void ShaderUtils::InitCombileAllShader()
{
	static bool isInited = false;
	if (isInited)
	{
		return;
	}
	std::wstring shaderfolder = L"";
#pragma region DetermineShaderPath
	if (IsDebuggerPresent() == TRUE)
	{
#ifdef _DEBUG //Debug Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Debug\\Shaders\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Debug\\Shaders\\";
#endif
#else //Release Mode
#ifdef _WIN64 //x64
		shaderfolder = L"..\\x64\\Release\\Shaders\\";
#else  //x86 (Win32)
		shaderfolder = L"..\\Release\\Shaders\\";
#endif
#endif
	}
	std::wstring vAllVertexShader[] = { 
		L"Basic_2D_VS.cso" 
		,L"Basic_Depth_VS.cso"
		,L"Basic_BasePass_VS.cso"
		,L"Basic_Light_VS.cso"
		,L"Default_VS.cso"};
	std::wstring vAllPixelShader[] = { 
		 L"Basic_2D_PS.cso" 
		,L"Basic_Depth_PS.cso"
		,L"Basic_BasePass_PS.cso"
		,L"Basic_Light_PS.cso"
		,L"Default_PS.cso" 
	};

	ShaderResource *VComShader;
	for (int i = 0, len = ARRAYSIZE(vAllVertexShader); i < len; i++)
	{
		FShaderCompilerOutput* vOutCompiler = new FShaderCompilerOutput();
		vOutCompiler->FileName = vAllVertexShader[i];
		vOutCompiler->mTarget.Frequency = EShaderFrequency::SF_Vertex;

		VComShader = new ShaderResource(vOutCompiler);
		VComShader->InitRHI();
	}
	for (int i = 0, len = ARRAYSIZE(vAllPixelShader); i < len; i++)
	{
		FShaderCompilerOutput* vOutCompiler = new FShaderCompilerOutput();
		vOutCompiler->FileName = vAllPixelShader[i];
		vOutCompiler->mTarget.Frequency = EShaderFrequency::SF_Pixel;

		VComShader = new ShaderResource(vOutCompiler);
		VComShader->InitRHI();
	}
	isInited = true;
}

ShaderResource* ShaderUtils::GetShaderResource(std::wstring shaderFileName)
{
	return ShaderResource::GetShaderResourceByName(shaderFileName);
}
