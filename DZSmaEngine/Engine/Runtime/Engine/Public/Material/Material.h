#pragma  once;
#include "MaterialOutput.h"
#include "MaterialInput.h"
#include "ConstantBufferTypes.h"
class BaseMaterial
{
public:
	BaseMaterial();
	MaterialInputNode* AmbientNode;
	MaterialInputNode* DiffuseNode;
	MaterialInputNode* SpecularNode;
	MaterialInputNode* ReflectNode;

public:
	MaterialOutPut* CalculateMaterialOutput();
	void FillShader(ShaderMaterial* pShaderMeterial);
};
