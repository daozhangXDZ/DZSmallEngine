#include "Material/MaterialUtils.h"

void MaterialUtil::fillShaderMaterial(BaseMaterial* material, ShaderMaterial* shaderOut)
{
	material->FillShader(shaderOut);
};