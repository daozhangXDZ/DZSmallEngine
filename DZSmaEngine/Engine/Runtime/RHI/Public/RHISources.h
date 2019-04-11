#pragma once
#include "CoreMinimal.h"
class RHIResource
{

};

class RHIVertexShader : public RHIResource {};
class RHIPixelShader : public RHIResource {};

typedef RHIVertexShader* RHIVertexShaderParamRef;

struct UniFormLayout 
{
	uint32 ConstantBufferSize;
	void*  Resource;
};

class RHIUniFormBuffer : public RHIResource
{
public:
	UniFormLayout* Layout;
};

typedef RHIUniFormBuffer* RHIUniFormBufferRef;