#pragma  once;
#include "MaterialOutput.h"
#include "MaterialInput.h"
#include "ConstantBufferTypes.h"
#include "RHISources.h"

enum MaterialType
{
	Opera = 0,
	Mask = 1,
	Trsulute = 2,
};	

class BaseMaterial
{
public:
	BaseMaterial();
	MaterialInputNode*					AmbientNode;
	MaterialInputNode*					DiffuseNode;
	MaterialInputNode*					SpecularNode;
	MaterialInputNode*					ReflectNode;
	RHIVertexShaderRef					mVertexShader;
	RHIPixelShaderRef					mPixelShader;
	RHIVertexInputElementRef			mInputElement;
	RHIVertexLayoutRef					mInputLayout;

	/**
	 * ����ͼ
	 */
	RHIShaderResourceViewRef			mMainTexture = nullptr;
	/**
	 * ������ͼ������ᷢ��PSO��ȥ
	 */
	RHIShaderResourceViewRef			mNormalTexture = nullptr;

	MaterialType materialType = MaterialType::Opera;

public:
	MaterialOutPut* CalculateMaterialOutput();
	void FillShader(ShaderMaterial* pShaderMeterial);
};
