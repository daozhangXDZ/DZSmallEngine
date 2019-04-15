#pragma once
#include "Material.h"
#include "ConstantBufferTypes.h"
class MaterialUtil
{
public:
	static void fillShaderMaterial(BaseMaterial* material, ShaderMaterial* shaderOut);
};