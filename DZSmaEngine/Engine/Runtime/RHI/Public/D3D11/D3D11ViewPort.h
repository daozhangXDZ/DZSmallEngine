#pragma once
#include "RHISources.h"
#include "D3D11DynamicRHI.h"
#include "PixelFormat.h"
class RHID3D11ViewPort :public RHIViewPort
{
public:
	RHID3D11ViewPort(class D3D11DynamicRHI* InD3DRHI, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, EPixelFormat InPreferredPixelFormat);
public:
	/**
	 * 获取平台本地交换链
	 */
	virtual void* GetNativeSwapChain() const override;
	/**
	 * 获取后背缓冲区
	 */
	virtual void* GetNativeBackBufferTexture() const override;
	/**
	 * 获取后背缓冲区的BackBuffer 的RenderTarget
	 */
	virtual void* GetNativeBackBufferRT() const override;

public:
	D3D11DynamicRHI*								D3DRHI;
	HWND											WindowHandle;
	uint32											ViewSizeX;
	uint32											ViewSizeY;
	EPixelFormat									PreferredPixelFormat;
	Microsoft::WRL::ComPtr < IDXGISwapChain	>		SwapChain;
	FD3D11Texture2D BackBuffer;
};