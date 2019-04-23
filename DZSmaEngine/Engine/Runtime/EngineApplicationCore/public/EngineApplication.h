#pragma once
#include "EngineWindow.h"
#include "EngineApplicationMIisc.h"
#include "GeneralApplication/DeviceInput.h"
class EngineApplication
{
public:
	EngineApplication();
	static EngineApplication* get();

	void Start();

	void AddWindow(EngineWindow* InEngineWindows, const bool bShowImmediately = true);

	GeneralWindow* MakeWindow(EngineWindow* InSlateWindow, const bool bShowImmediately);

	void Tick(float dt);

	void DrawWindows();

private:
	void TickApplication(float dt);

	void PrivateDrawWindows();

private:
	IDeviceInput_Receiver* currInputReceive;
	GeneralApplication* currApplicationMisc = nullptr;

	/** Application singleton */
	static EngineApplication* CurrentApplication;
	bool isStartApp = false;
};
