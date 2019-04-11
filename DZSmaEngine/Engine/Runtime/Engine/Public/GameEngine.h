#pragma once
#include "BaseEngine.h"
#include "Scene.h"
#include "SceneRender.h"
#include "GeneralApplication/DeviceInput.h"
#include "EngineGlobal.h"

class GameEngine :public BaseEngine, public IDeviceInput_Receiver
{
public:
	virtual void Init() final override
	{
		mSceneProxy = new SceneProxy();
		mSceneProxy->initScene();


		{
			staticRenderProxy = new std::vector<PrimitiveSceneProxy *>();
			std::vector<PrimitiveComponent*> primitiveComList = mSceneProxy->GetScenePrimitive();
			for (int i = 0; i < primitiveComList.size(); i++)
			{
				PrimitiveSceneProxy* vProxy = primitiveComList[i]->getCurrRenderProxy();
				vProxy->InitRender();
				staticRenderProxy->push_back(vProxy);
			}
		}
		GEngineApliation->Register_input(this);
	};

	virtual void Tick() final override 
	{
		if (staticRenderProxy == nullptr)
			return;
		mSceneProxy->Tick(0.1f);
		SceneRender* CurrRender = SceneRender::GetShaderRender();
		CurrRender->Render(staticRenderProxy);
		CurrRender->UpdateViewProject(&(mSceneProxy->GetMainCameraDesc()),true);
	};

	virtual void Exit() final override 
	{
		
	}


public:
	virtual void receive_KeyBode(EnKeyCode keyOne) 
	{
		switch (keyOne)
		{
		case W:
			mSceneProxy->GetCamera()->AdjustPosition(mSceneProxy->GetCamera()->GetForwardVector() * mCameraSpeed);
			break;
		case S:
			mSceneProxy->GetCamera()->AdjustPosition(mSceneProxy->GetCamera()->GetBackwardVector() * mCameraSpeed);
			break;
		case A:
			mSceneProxy->GetCamera()->AdjustPosition(mSceneProxy->GetCamera()->GetLeftVector() * mCameraSpeed);
			break;
		case D:
			mSceneProxy->GetCamera()->AdjustPosition(mSceneProxy->GetCamera()->GetRightVector() * mCameraSpeed);
			break;
		case Z:
			mSceneProxy->GetCamera()->AdjustPosition(0.0, -mCameraSpeed,0.0);
			break;
		case SPACE:
			mSceneProxy->GetCamera()->AdjustPosition(0.0, mCameraSpeed, 0.0);
			break;
		default:
			break;
		}
	};

	virtual void receive_MouseMove(float x, float y) 
	{
		mSceneProxy->GetCamera()->AdjustRotation(y * 0.01f, x * 0.01f, 0);
	};


private:
	float mCameraSpeed = 0.005;
	SceneProxy* mSceneProxy;
	std::vector<PrimitiveSceneProxy*>* staticRenderProxy;
};