#include "TestRenderPipelineUtil.h"
#include "Scene.h"
#include "SceneBasePase_Check.h"

SceneProxy* currCheckScene = nullptr;
void TestRenderPipelineUtil::InitCheckScene()
{
	currCheckScene = new SceneTest01();
}
