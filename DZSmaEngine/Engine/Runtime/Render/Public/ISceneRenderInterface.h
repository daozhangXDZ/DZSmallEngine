#pragma once
#include "CoreMinimal.h"
#include "PrimitiveSceneInfo.h"
class ISceneRenderInterface 
{
public:
	virtual	TArray<PrimitiveSceneInfo*> GetDepthSceneInfoList() = 0;
	virtual TArray<PrimitiveSceneInfo*> GetBaseSceneInfoList() = 0;
};