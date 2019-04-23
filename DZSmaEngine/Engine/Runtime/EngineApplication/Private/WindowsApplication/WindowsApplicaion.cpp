#include "WindowsApplication/WindowsApplicaion.h"
#include "WindowsApplication/WindowsWindows.h"

GeneralWindow* WindowsApplication::MakerWindow()
{
	return new WindowsWindow;
}

void WindowsApplication::InitializeWindow(GeneralWindow* InWindow, GeneralWindowDesc* InDefinition, GeneralWindow* InParent, const bool bShowImmediately)
{
	WindowsWindow* Window = dynamic_cast<WindowsWindow*>(InWindow);
	if (Window)
	{
		Window->InitWindows(InDefinition);
	}
}

void WindowsApplication::OpenWindow(GeneralWindow * InWindow)
{
	WindowsWindow* Window = dynamic_cast<WindowsWindow*>(InWindow);
	if (Window)
	{
		
	}
}