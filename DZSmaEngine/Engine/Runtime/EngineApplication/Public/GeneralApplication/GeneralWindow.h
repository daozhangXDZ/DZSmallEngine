#pragma once
#include "CoreMinimal.h"
#include "GeneralWindowDesc.h"
#include "DeviceInput.h"
class GeneralWindow
{
public:
	virtual void	InitWindows(GeneralWindowDesc* desc) {};
	virtual void**  GetHWD() { return nullptr; };
	virtual bool	RunWindows() { return false; };
	virtual void    Open() {};
	virtual void    Close() {};
	virtual void    Register_input(IDeviceInput_Receiver* pReceive)
	{
		mInputReceive = pReceive;
		IsHasInputReceive = true;
	}
	virtual void     UnRegister_Input()
	{
		mInputReceive = nullptr;
		IsHasInputReceive = false;

	}
protected:
	IDeviceInput_Receiver* mInputReceive = nullptr;
	bool IsHasInputReceive = false;
public:
	int width;
	int height;
	FString title;
	FString WindowsClassName;
	FString titleDesc;
};