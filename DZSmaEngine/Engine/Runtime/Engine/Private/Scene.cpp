#include "Scene.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include "Components/CombineMesh.h"
#include "Components/CubeMesh.h"
#include "Components/PanelMeshComponent.h"

#include "Components/StaticMeshComponent.h"

SceneProxy::SceneProxy():SceneComponent()
{
	SetPosition(0.0, 0.0, 0.0);
	SetRotation(0.0, 0.0, 0.0);
	SetScale(1.0, 1.0, 1.0);
}


bool SceneProxy::initScene()
{
	InitCamera();
	InitMeshObj();
	return true;

}

void SceneProxy::InitCamera()
{
	mCameraComponent = new BaseCameraComponent();
	float AspectRatio = mCameraComponent->AspectRatio(800, 600);
	mCameraComponent->SetProjectionValues(90.0f, AspectRatio, 0.1, 1000.0f);
	mCameraComponent->SetPosition(0.0f, 0.0f, -1.0f);
	mCameraComponent->SetLookAtPos(0.0f, 0.0f, 1.0f);
}

void SceneProxy::InitMeshObj()
{
	__ObjList.clear();
	try
	{
		InitExtendMode(XMFLOAT3(0, -1, 2), XMFLOAT3(0, 0, 0), XMFLOAT3(0.5f, 0.5f, 0.5f), "Data\\Objects\\Nanosuit\\Nanosuit.obj", L"Data\\Textures\\p3.jpg", 1.0f);

		InitCubeMode(XMFLOAT3(3, 0, 2), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), L"Data\\Textures\\p1.jpg", 1.0f);
		InitCubeMode(XMFLOAT3(-3, 0, 2), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), L"Data\\Textures\\p2.jpg", 1.0f);
		InitCubeMode(XMFLOAT3(0, 0, 10), XMFLOAT3(0, 0, 0), XMFLOAT3(90, 90, 1), L"Data\\Textures\\SampleTextureExam.PNG", 1.0f);
		InitPanelMode(XMFLOAT3(0, -1, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(10, 1, 10), L"Data\\Textures\\p3.jpg", 1.0f);

		InitStaticMesh(XMFLOAT3(10, 3, 2), XMFLOAT3(0, 0, 0), XMFLOAT3(0.06f, 0.06f, 0.06f), "Data\\Objects\\evr\\SM_MERGED_wood_2.OBJ", L"Data\\Objects\\evr\\Wood4.jpg", 1.0f);
		InitStaticMesh(XMFLOAT3(-10, 3, 2), XMFLOAT3(0, 0, 0), XMFLOAT3(0.06f, 0.06f, 0.06f), "Data\\Objects\\evr\\SM_MERGED_wood_2.OBJ", L"Data\\Objects\\evr\\Wood4.jpg", 1.0f);
	}
	catch (COMException & exception)
	{
		ErrorLogger::Log(exception);
		return;
	}
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
}

void SceneProxy::AddOneStaticPrimitiveComponent(PrimitiveComponent * obj)
{
	__ObjList.push_back(obj);
	obj->Initialize();
}

void SceneProxy::AddOneDynamicPrimitiveComponent(PrimitiveComponent * obj)
{
	__ObjList.push_back(obj);
	obj->Initialize();
}

std::vector<PrimitiveComponent*> SceneProxy::GetScenePrimitive()
{
	return __ObjList;
}

ViewPortDesc SceneProxy::GetMainCameraDesc()
{
	return mViewPortdesc;
}



///////////////////////////////---------------------------���Դ���--------------------------------------///////////////////////////////////////////

void SceneProxy::InitExtendMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha)
{
	//CombineMeshComponent* pMeshMode = new CombineMeshComponent(modelPath, mainTexturePath);
	//pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	//pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	//pMeshMode->SetScale(sca.x, sca.y, sca.z);
	//pMeshMode->Initialize();
	///*if (currRenderCard)
	//{
	//	currRenderCard->SetupPrimitiveSceneProxy(pMeshMode->getCurrRenderProxy());
	//}*/
	//AddOneStaticPrimitiveComponent(pMeshMode);
}

void SceneProxy::InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha)
{
	CubeMeshComponent* pMeshMode = new CubeMeshComponent(mainTexturePath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);
}

void SceneProxy::InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha)
{
	PanelMeshComponent* pMeshMode = new PanelMeshComponent(mainTexturePath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);
}


void SceneProxy::InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::wstring mainTexturePath, float pAlpha)
{
	/*PanelMeshComponent* pMeshMode = new PanelMeshComponent(mainTexturePath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->Initialize();
	if (currRenderCard)
	{
		currRenderCard->SetupPrimitiveSceneProxy(pMeshMode->getCurrRenderProxy());
	}
	AddOneStaticPrimitiveComponent(pMeshMode);*/
}

void SceneProxy::InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha)
{
	InitStaticMesh(pos, rot, sca, modelPath, mainTexturePath, pAlpha, XMFLOAT4(1.0, 1.0, 1.0, 1.0), XMFLOAT4(1.0, 1.0, 1.0, 1.0), XMFLOAT4(0.0, 0.0, 0.0, 1.0));
}

void SceneProxy::InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, std::wstring mainTexturePath, float pAlpha, XMFLOAT4 Ambient, XMFLOAT4 Spec, XMFLOAT4 Diffcuse)
{
	StaticMeshComponent* pMeshMode = new StaticMeshComponent(modelPath,mainTexturePath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->Initialize();
	pMeshMode->mMaterilDesc.Ambient = Ambient;
	pMeshMode->mMaterilDesc.Diffuse = Diffcuse;
	pMeshMode->mMaterilDesc.Specular = Spec;
	AddOneStaticPrimitiveComponent(pMeshMode);
}
