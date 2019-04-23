#include "EngineWindow.h"
#include "EngineGlobal.h"

void EngineWindow::SetNativeWindow(GeneralWindow* InNativeWindow)
{
	nativeWindow = InNativeWindow;
}

bool EngineWindow::Run()
{
	return nativeWindow->RunWindows();
}
void EngineWindow::Exit()
{
	nativeWindow->Close();
}

void EngineWindow::SetWindowMode(bool isFullScreen)
{
	ViewPortRHI = GDynamicRHI->RHICreateViewport(GetOSHandle(), width, height, false, EPixelFormat::PF_B8G8R8A8);
}

void EngineWindow::OpenWindow()
{
	nativeWindow->Open();
}

void** EngineWindow::GetOSHandle()
{
	return nativeWindow->GetHWD();
}

void EngineWindow::Register_input(IDeviceInput_Receiver* pReceive)
{
	if (nativeWindow != nullptr)
	{
		nativeWindow->Register_input(pReceive);
	}
}

RHIViewPortRef EngineWindow::getViewPortRHI()
{
	return ViewPortRHI;
}