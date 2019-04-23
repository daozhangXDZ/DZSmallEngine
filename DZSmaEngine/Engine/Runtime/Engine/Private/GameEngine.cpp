#include "GameEngine.h"
void GameEngine::Init()
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
	EngineApplication::get()->Register_input(this);
};

void GameEngine::Tick(float dt)
{
	if (staticRenderProxy == nullptr)
		return;
	mSceneProxy->Tick(0.1f);
	if (CurrRender == nullptr)
	{
		RHICMDList = new RHICommandListImmediate();
		CurrRender = SceneRender::GetShaderRender();
		CurrRender->InitRes(RHICMDList);
	}
	CurrRender->Render(RHICMDList, staticRenderProxy);
	CurrRender->UpdateViewPort(RHICMDList, &(mSceneProxy->GetMainCameraDesc()), true);
};

void GameEngine::Exit()
{

}


void GameEngine::receive_KeyBode(EnKeyCode keyOne)
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
		mSceneProxy->GetCamera()->AdjustPosition(0.0, -mCameraSpeed, 0.0);
		break;
	case SPACE:
		mSceneProxy->GetCamera()->AdjustPosition(0.0, mCameraSpeed, 0.0);
		break;
	default:
		break;
	}
};

void GameEngine::receive_MouseMove(float x, float y)
{
	mSceneProxy->GetCamera()->AdjustRotation(y * 0.01f, x * 0.01f, 0);
};

EngineWindow* GameEngine::CreateGameWindow()
{
	EngineWindow* windows = new EngineWindow();
	windows->width = 800;
	windows->height = 600;
	windows->title = "EngineMainWindows";
	windows->titleDesc = "EngingMain";
	windows->WindowsClassName = "EngineMainWindows";
	EngineApplication::get()->AddWindow(windows, true);
	windows->SetWindowMode(false);
	windows->OpenWindow();
	EngineApplication::get()->Tick(0.0f);
	return windows;
}