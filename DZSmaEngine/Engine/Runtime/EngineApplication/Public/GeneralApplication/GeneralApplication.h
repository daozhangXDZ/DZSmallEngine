#pragma once
#include "GeneralWindow.h"
#include "GeneralWindowDesc.h"
class GeneralApplication
{
public:

	virtual GeneralWindow* MakerWindow()
	{
		return nullptr;
	}

	virtual void InitializeWindow(GeneralWindow* Window, GeneralWindowDesc* InDefinition, GeneralWindow* InParent, const bool bShowImmediately) { }


	virtual void OpenWindow(GeneralWindow * pWin)
	{
	
	}
};