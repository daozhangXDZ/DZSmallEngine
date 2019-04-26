#pragma once
#include "BaseEngine.h"
#include "Scene.h"
#include "SceneRender.h"
#include "GeneralApplication/DeviceInput.h"
#include "EngineGlobal.h"
class GameEngine :public BaseEngine, public IDeviceInput_Receiver
{
public:
	virtual void Init() final override;

	virtual void Tick(float dt) final override;

	virtual void Exit() final override;

public:
	virtual void receive_KeyBode(EnKeyCode keyOne);

	virtual void receive_MouseMove(float x, float y);

	static  EngineWindow* CreateGameWindow();

private:
	float mCameraSpeed = 0.005f;
	SceneProxy* mSceneProxy;
	SceneRender* CurrRender;
	RHICommandListImmediate* RHICMDList;
};

