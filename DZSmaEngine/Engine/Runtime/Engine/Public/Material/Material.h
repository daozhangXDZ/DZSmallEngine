#pragma  once;
#include "MaterialOutput.h"
#include "MaterialInput.h"
#include "ConstantBufferTypes.h"
#include "RHISources.h"
class BaseMaterial
{
public:
	BaseMaterial();
	MaterialInputNode* AmbientNode;
	MaterialInputNode* DiffuseNode;
	MaterialInputNode* SpecularNode;
	MaterialInputNode* ReflectNode;
	RHIVertexShaderRef					mVertexShader;
	RHIPixelShaderRef					mPixelShader;
	RHIVertexInputElementRef			mInputElement;
	RHIVertexLayoutRef					mInputLayout;

public:
	MaterialOutPut* CalculateMaterialOutput();
	void FillShader(ShaderMaterial* pShaderMeterial);
};
