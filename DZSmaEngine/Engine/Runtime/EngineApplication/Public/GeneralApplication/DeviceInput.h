#pragma once
#include "CoreMinimal.h"
enum EnKeyCode
{
	W = 1,
	S = 2,
	A = 4,
	D = 8,
	Z = 16,
	SPACE = 32
};

class IDeviceInput_Receiver
{
public:
	virtual void receive_KeyBode(EnKeyCode keyOne) {};
	virtual void receive_MouseMove(float x, float y) {};
};