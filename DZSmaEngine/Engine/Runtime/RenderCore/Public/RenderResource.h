#pragma once
#include "RHISources.h"

class VertexBuffer : public RHIResource
{
public:
	RHIVertexBuffer mVertexBuffer;
};

class IndexBuffer : public RHIResource
{
public:
	RHIIndexBuffer mIndexBuffer;
};