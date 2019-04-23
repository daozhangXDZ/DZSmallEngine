#include "D3D11/D3D11DynamicRHI.h"

void D3D11DynamicRHI::Tick()
{
	DynamicRHI::Tick();
	BeginDrawViewPort();
	
	EndDrawViewPort();
};

void D3D11DynamicRHI::Exit()
{
	DynamicRHI::Exit();
}