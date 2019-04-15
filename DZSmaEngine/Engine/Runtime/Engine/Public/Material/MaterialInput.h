#pragma once
#include "CoreMinimal.h"
struct MaterialInputNode
{
	MaterialInputNode() 
	{
	
	}
	float r;
	float g;
	float b;
	float a;

	void fill(XMFLOAT4 value);
};