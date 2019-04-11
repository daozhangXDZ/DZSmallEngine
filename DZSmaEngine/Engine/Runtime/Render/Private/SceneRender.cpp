#include "SceneRender.h"
#include "SimpleShadingRender.h"

SceneRender * SceneRender::GetShaderRender()
{
	return new SimpleShadingRender();
}
