#include "Material/Material.h"
BaseMaterial::BaseMaterial()
{
	AmbientNode = new MaterialInputNode();
	DiffuseNode = new MaterialInputNode();
	SpecularNode = new MaterialInputNode();
	ReflectNode = new MaterialInputNode();
}

MaterialOutPut* BaseMaterial::CalculateMaterialOutput()
{
	MaterialOutPut* vOutput = new MaterialOutPut();
	vOutput->Ambient = XMFLOAT4(AmbientNode->r, AmbientNode->g, AmbientNode->b, AmbientNode->a);
	vOutput->Diffuse = XMFLOAT4(DiffuseNode->r, DiffuseNode->g, DiffuseNode->b, DiffuseNode->a);
	vOutput->Specular = XMFLOAT4(SpecularNode->r, SpecularNode->g, SpecularNode->b, SpecularNode->a);
	vOutput->Reflect = XMFLOAT4(ReflectNode->r, ReflectNode->g, ReflectNode->b, ReflectNode->a);
	vOutput->isUseDiffTexture = mMainTexture != nullptr;
	vOutput->isUseNormalTexture = mNormalTexture != nullptr;
	return vOutput;
}

void BaseMaterial::FillShader(ShaderMaterial* pShaderMeterial)
{
	pShaderMeterial->Ambient = XMFLOAT4(AmbientNode->r, AmbientNode->g, AmbientNode->b, AmbientNode->a);
	pShaderMeterial->Diffuse = XMFLOAT4(DiffuseNode->r, DiffuseNode->g, DiffuseNode->b, DiffuseNode->a);
	pShaderMeterial->Specular = XMFLOAT4(SpecularNode->r, SpecularNode->g, SpecularNode->b, SpecularNode->a);
	pShaderMeterial->Reflect = XMFLOAT4(ReflectNode->r, ReflectNode->g, ReflectNode->b, ReflectNode->a);
	pShaderMeterial->diffTextureUsed = mMainTexture != nullptr ? 1 : 0;
	pShaderMeterial->normalTextureUsed = mNormalTexture != nullptr ? 1 : 0;
	/*if (materialType == MaterialType::Trsulute)
	{
		pShaderMeterial->materialType = materialType;
	}*/
	pShaderMeterial->materialType = materialType;
};
