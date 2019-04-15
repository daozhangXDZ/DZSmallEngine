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
	std::wstring vAllVertexShader[] = { L"Basic_VS_3D.cso" };
	std::wstring vAllPixelShader[] = { 
		L"Basic_PS_3D.cso" 
		,L"Basic_PS_3D_Emit.cso" 
		,L"Basic_PS_3D_PBR_01.cso" 
		,L"Basic_PS_2D.cso" };

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
