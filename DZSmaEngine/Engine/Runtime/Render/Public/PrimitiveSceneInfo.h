#pragma once
#include "primitivesceneproxy.h"
#include "Material/Material.h"
#include "StaticMesh.h"
class PrimitiveSceneInfo
{
public:
	PrimitiveSceneProxy* RenderProxy;
	XMMATRIX worldMaterix;
	BaseMaterial* materia;
	StaticMesh* mesh;
};