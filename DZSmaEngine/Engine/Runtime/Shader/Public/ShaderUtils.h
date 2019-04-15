#pragma once
#include "CoreMinimal.h"
#include "Shader.h"
#include "RHISources.h"
class ShaderUtils
{
public:
	static void InitCombileAllShader();
	static ShaderResource* GetShaderResource(std::wstring shaderFileName);
};