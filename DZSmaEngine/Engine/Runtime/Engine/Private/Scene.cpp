#include "Scene.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"


SceneProxy::SceneProxy():SceneComponent()
{
	SetPosition(0.0, 0.0, 0.0);
	SetRotation(0.0, 0.0, 0.0);
	SetScale(1.0, 1.0, 1.0);
}


bool SceneProxy::initScene()
{
	return true;
}

void SceneProxy::Tick(float dt)
{
	SceneComponent::Tick(dt);
	for (int i=0; i< __ObjList.size(); i++)
	{
		__ObjList[i]->Tick(dt);
	}
	mViewPortdesc.viewMat = mCameraComponent->GetViewMatrix();
	mViewPortdesc.ProjMat = mCameraComponent->GetProjectionMatrix();
	mViewPortdesc.eyepos = mCameraComponent->GetPositionFloat3();
}

void SceneProxy::AddOneStaticPrimitiveComponent(PrimitiveComponent * obj)
{
	__ObjList.push_back(obj);
	//obj->Initialize();
	{
		PrimitiveSceneInfo* info = obj->GetSceneInfo();
		SceneDepthInfo.push_back(info);
		SceneRenderInfo.push_back(info);
	}
}

void SceneProxy::AddOneDynamicPrimitiveComponent(PrimitiveComponent * obj)
{
	__ObjList.push_back(obj);
	//obj->Initialize();
}

std::vector<PrimitiveComponent*> SceneProxy::GetScenePrimitive()
{
	return __ObjList;
}

ViewPortDesc SceneProxy::GetMainCameraDesc()
{
	return mViewPortdesc;
}

TArray<PrimitiveSceneInfo*> SceneProxy::GetDepthSceneInfoList()
{
	return SceneDepthInfo;
}

TArray<PrimitiveSceneInfo*> SceneProxy::GetBaseSceneInfoList()
{
	return SceneRenderInfo;
}

BaseCameraComponent * SceneProxy::GetCamera()
{
	return mCameraComponent;
}