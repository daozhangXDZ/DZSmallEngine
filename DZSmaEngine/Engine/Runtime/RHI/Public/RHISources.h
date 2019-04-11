#pragma once
#include "CoreMinimal.h"
class RHIResource
{

};

class RHIRenderTarget :public RHIResource
{

};

typedef RHIRenderTarget* RHIRenderTargetRef;
typedef RHIRenderTarget* RHIRenderTargetParamRef;


class RHIDepthTarget :public RHIResource
{

};

typedef RHIDepthTarget* RHIDepthTargetRef;
typedef RHIDepthTarget* RHIDepthTargetParamRef;


//////////////////////////////////////////////////////////////////////////
class RHIVertexShader : public RHIResource {};
class RHIPixelShader : public RHIResource {};
class RHIComputerShader : public RHIResource {};
class RHIVertexInputElement :public RHIResource
{
public:
	void* elementsDesc;
	UINT elementsNumber;

};

class RHIVertexLayout	: public RHIResource 
{
public:
	RHIVertexInputElement* element;
};

typedef RHIVertexShader* RHIVertexShaderRef;
typedef RHIVertexShader* RHIVertexShaderParamRef;

typedef RHIPixelShader* RHIPixelShaderRef;
typedef RHIPixelShader* RHIPixelShaderParamRef;

typedef RHIComputerShader* RHIComputerShaderRef;
typedef RHIComputerShader* RHIComputerShaderParamRef;

typedef RHIVertexInputElement* RHIVertexInputElementRef;
typedef RHIVertexInputElement* RHIVertexInputElementParamRef;

typedef RHIVertexLayout* RHIVertexLayoutRef;
typedef RHIVertexLayout* RHIVertexLayoutParamRef;


//////////////////////////////////////////////////////////////////////////

struct UniFormLayout 
{
	uint32 ConstantBufferSize;
	void*  Resource;
};
typedef UniFormLayout* UniFormLayoutRef;
typedef UniFormLayout* UniFormLayoutParamRef;

class RHIUniFormBuffer : public RHIResource
{
public:
	UniFormLayoutRef Layout;

	RHIVertexShaderRef vertecShader;
	RHIPixelShaderRef pixelShader;
	RHIComputerShaderRef computerShader;
};

typedef RHIUniFormBuffer* RHIUniFormBufferRef;
typedef RHIUniFormBuffer* RHIUniFormBufferParamRef;


//////////////////////////////////////////////////////////////////////////
class RHIShaderResourceView :public RHIResource
{

};
typedef RHIShaderResourceView* RHIShaderResourceViewRef;
typedef RHIShaderResourceView* RHIShaderResourceViewParamRef;


class RHIVertexBuffer : public RHIResource
{

};

class RHIIndexBuffer :public RHIResource
{

};

typedef RHIVertexBuffer* RHIVertexBufferRef;
typedef RHIVertexBuffer* RHIVertexBufferParamRef;

typedef RHIIndexBuffer* RHIIndexBufferRef;
typedef RHIIndexBuffer* RHIIndexBufferParamRef;

