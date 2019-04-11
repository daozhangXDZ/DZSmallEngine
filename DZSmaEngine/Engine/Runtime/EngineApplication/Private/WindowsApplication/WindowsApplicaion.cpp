#include "WindowsApplication/WindowsApplicaion.h"
#include "WindowsApplication/WindowsWindows.h"

GeneralWindow* WindowsApplication::MakerWindow(EngineWindowDesc* desc)
{
	return new WindowsWindow;
}

void WindowsApplication::OpenWindow(GeneralWindow * pWin)
{
	return;
}