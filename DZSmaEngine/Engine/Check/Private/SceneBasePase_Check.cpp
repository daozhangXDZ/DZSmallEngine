#include "SceneBasePase_Check.h"
#include "Components/CubeMesh.h"
#include "Components/PanelMeshComponent.h"
#include "Components/DirectionLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Material/MaterialUtils.h"
#include "LogUtil/COMException.h"
#include "LogUtil/ErrorLogger.h"

bool SceneTest01::initScene()
{
	InitCamera();
	InitMeshObj();
	InitLight();
	return true;

}

void SceneTest01::InitCamera()
{
	mCameraComponent = new BaseCameraComponent();
	float AspectRatio = mCameraComponent->AspectRatio(800, 600);
	mCameraComponent->SetProjectionValues(90.0f, AspectRatio, 0.1f, 1000.0f);
	mCameraComponent->SetPosition(0.0f, 10.0f, -3.0f);
	mCameraComponent->SetLookAtPos(0.0f, 2.0f, 3.0f);
}


void SceneTest01::InitLight()
{
	//方向光
	for (int i = 0; i < 1; i++)
	{
	/*	vRarelyCSB.dirLight[i].Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 2.0f);
		vRarelyCSB.dirLight[i].Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		vRarelyCSB.dirLight[i].Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
		vRarelyCSB.dirLight[i].Direction = XMFLOAT3(-0.577f, -0.577f, 0.577f);*/
		LightComponent* DireLight = new DirectionLightComponent();
		DireLight->SetPosition(2.0f, 5.0f, -30.0f);
		DireLight->SetRotation(0.0f, 0.0f, 0.45f);
		DireLight->SetScale(1.0f, 1.0f, 1.0f);
		
		DireLight->SetAmbientColor(0.5f, 0.5f, 0.5f, 2.0f);
		DireLight->SetDiffuseColor(0.5f, 0.5f, 0.5f, 1.0f);
		DireLight->SetSpecularColor(0.1f, 0.1f, 0.1f, 1.0f);
		AddOneStaticLightComponent(DireLight);
	}
}


////////////////////////////////////----------------------------------------------------//////////////////////////////////////
void SceneTest01::InitMeshObj()
{
	__ObjList.clear();
	try
	{
		//材质测试
		{
			int j = -1;
			InitCubeMode(XMFLOAT3(j * 10.0f, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Textures\\p1.jpg", L"",
					L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
			j += 1;
			InitCubeMode(XMFLOAT3(j * 10.0f, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Mask,
					L"Data\\Textures\\p2_alpha.png", L"",
					L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
					XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
					XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
					XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
					XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
				)
			);
			j += 1;
			InitCubeMode(XMFLOAT3(10.0f * j, 4.0f, 10.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f),
				MaterialUtil::CreateOneMateria(
					MaterialType::Opera,
					L"Data\\Textures\\p2.jpg", L"Data\\Textures\\p2_NORM.png",
					L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
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
				L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
				XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
				XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f),
				XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f),
				XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f)
			)
		);
		InitCubeMode(XMFLOAT3(0.0f, 4.0f, 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(90.0f, -2.0f, 90.0f),
			MaterialUtil::CreateOneMateria(
				MaterialType::Opera,
				L"Data\\Textures\\p2.jpg", L"",
				L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
				XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
				XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f),
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
					L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
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
					L"Basic_Light_VS.cso", L"Basic_Light_PS.cso",
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
void SceneTest01::InitCubeMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial)
{
	CubeMeshComponent* pMeshMode = new CubeMeshComponent();
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);
}

void SceneTest01::InitPanelMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial)
{
	/*PanelMeshComponent* pMeshMode = new PanelMeshComponent();
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();
	AddOneStaticPrimitiveComponent(pMeshMode);*/
}


void SceneTest01::InitSphereMode(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, BaseMaterial* MainMaterial)
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


void SceneTest01::InitStaticMesh(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string modelPath, BaseMaterial* MainMaterial)
{
	/*StaticMeshComponent* pMeshMode = new StaticMeshComponent(modelPath);
	pMeshMode->SetPosition(pos.x, pos.y, pos.z);
	pMeshMode->SetRotation(rot.x, rot.y, rot.z);
	pMeshMode->SetScale(sca.x, sca.y, sca.z);
	pMeshMode->mMainMaterial = MainMaterial;
	pMeshMode->Initialize();

	AddOneStaticPrimitiveComponent(pMeshMode);*/
}

///////////////////////////////////---------------------------测试代码End--------------------------------------///////////////////////////////////////