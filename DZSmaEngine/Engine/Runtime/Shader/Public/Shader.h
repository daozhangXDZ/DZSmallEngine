#pragma once
#include "CoreMinimal.h"
#include "RHISources.h"
#include "ShaderCore.h"
#include "RHICommandList.h"
#include <map>
#include <vector>





class RenderResource
{
public:
	RenderResource();
	RenderResource(std::wstring pFileName);
public:
	std::wstring mFileName;
};
/**
 * 作为Shader编译后的资源存放载体
 */
class ShaderResource :public RenderResource
{
private:
	FShaderTarget mTarget;
	
	RHIVertexShaderRef	vertexShader;
	RHIPixelShaderRef	pixelShader;

	

	static std::map<std::wstring, int> ShaderResourceIdMap;
	static std::vector<ShaderResource*> ShaderList;
public:
	ShaderResource();
	ShaderResource(FShaderCompilerOutput* outPut);
	static ShaderResource* GetShaderResourceByName(std::wstring pShaderName);
	RHIPixelShaderRef getPixelShader();
	RHIVertexShaderRef getVertexShader();
	bool InitRHI();
};


