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
	void Register_input(IDeviceInput_Receiver* pReceive);

private:
	void TickApplication(float dt);

	void PrivateDrawWindows();

	

private:
	IDeviceInput_Receiver* currInputReceive;
	GeneralApplication* currApplicationMisc = nullptr;
	/** List of active modal windows.  The last item in the list is the top-most modal window */
	TArray<EngineWindow*> ActiveModalWindows;

	/** Application singleton */
	static EngineApplication* CurrentApplication;
	bool isStartApp = false;
};
