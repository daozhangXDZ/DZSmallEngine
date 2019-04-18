#include "Scene.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"
#include "Components/CubeMesh.h"
#include "Components/PanelMeshComponent.h"
#include "Components/DirectionLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Material/MaterialUtils.h"

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
	InitLight();
	return true;

}

void SceneProxy::InitCamera()
{
	mCameraComponent = new BaseCameraComponent();
	float AspectRatio = mCameraComponent->AspectRatio(800, 600);
	mCameraComponent->SetProjectionValues(90.0f, AspectRatio, 0.1f, 1000.0f);
	mCameraComponent->SetPosition(0.0f, 0.0f, -1.0f);
	mCameraComponent->SetLookAtPos(0.0f, 0.0f, 1.0f);
}


void SceneProxy::InitLight()
{
	//方向光
	for (int i = 1; i < 1; i++)
	{
		LightComponent* DireLight = new DirectionLightComponent();
		DireLight->SetPosition(2.0f, 5.0f, 3.0f);
		DireLight->SetScale(1.0f, 1.0f, 1.0f);
		DireLight->SetLightColor(DFVector(0.5f, 0.0f, 0.0f));
		__LightList.push_back(DireLight);
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
	mViewPortdesc.eyepos = mCameraComponent->GetPositionFloat3();
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


////////////////////////////////////----------------------------------------------------//////////////////////////////////////
void SceneProxy::InitMeshObj()
{
	__ObjList.clear();
	try
	{
		 //材质测试
		{
			int j = -1;
			InitCubeMode(XMFLOAT3(j * 5.0f, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Textures\\p1.jpg", L"",
					L"Basic_VS_3D.cso", L"Basic_PS_3D.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
			j+=1;
			InitCubeMode(XMFLOAT3(j * 5.0f, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Mask,
					L"Data\\Textures\\p2_alpha.png", L"",
					L"Basic_VS_3D.cso", L"Basic_PS_3D.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
			j += 1;
			InitCubeMode(XMFLOAT3(5.0f * j, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Textures\\p2.jpg", L"Data\\Textures\\p2_NORM.png",
					L"Basic_VS_3D.cso", L"Basic_PS_3D_PBR_01.cso",
					XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
					XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
					XMFLOAT4(0.2f, 0.2f, 0.2f, 80.0f),
					XMFLOAT4(0.2f, 0.2f, 0.2f, 80.0f)
				)
			);
		}



		InitCubeMode(XMFLOAT3(0.0f, 0.0f, 50.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(90.0f, 90.0f, 1.0f),
			MaterialUtil::CreateOneMateria(
				MaterialType::Opera,
				L"Data\\Textures\\SampleTextureExam.PNG", L"",
				L"Basic_VS_3D.cso", L"Basic_PS_3D_PBR_01.cso",
				XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
				XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
				XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
				XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
			)
		);
		InitPanelMode(XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(10.0f, 1.0f, 10.0f),
			MaterialUtil::CreateOneMateria(
				MaterialType::Opera,
				L"Data\\Textures\\p3.jpg", L"",
				L"Basic_VS_3D.cso", L"Basic_PS_3D_PBR_01.cso",
				XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
				XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
				XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
				XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
			)
		);

		for (int i = 1; i < 10; i++)
		{
			InitStaticMesh(XMFLOAT3(20.0f + i * 2.0f, 5.0f + i * 4.0f, 30.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.06f, 0.06f, 0.06f), "Data\\Objects\\evr\\SM_MERGED_wood_2.OBJ",
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Objects\\evr\\Wood4.jpg", L"",
					L"Basic_VS_3D.cso", L"Basic_PS_3D.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
			InitStaticMesh(XMFLOAT3(-20.0f - i * 2.0f, 5.0f + i * 4.0f, 30.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.06f, 0.06f, 0.06f), "Data\\Objects\\evr\\SM_MERGED_wood_2.OBJ",
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Objects\\evr\\Wood4.jpg", L"",
					L"Basic_VS_3D.cso", L"Basic_PS_3D.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
		}





	}
	catch (COMException & exception)
	{
		ErrorLogger::Log(exception);
		return;
	}
}


///////////////////////////////---------------------------测试代码Begin--------------------------------------///////////////////////////////////////////
void SceneProxy::InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial)
{
	CubeMeshComponent* pMeshMode = new CubeMeshComponent();
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);
}

void SceneProxy::InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca,  BaseMaterial* MainMaterial)
{
	PanelMeshComponent* pMeshMode = new PanelMeshComponent();
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);
}


void SceneProxy::InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial)
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


void SceneProxy::InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, BaseMaterial* MainMaterial)
{
	StaticMeshComponent* pMeshMode = new StaticMeshComponent(modelPath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();
	
	AddOneStaticPrimitiveComponent(pMeshMode);
}

///////////////////////////////////---------------------------测试代码End--------------------------------------///////////////////////////////////////