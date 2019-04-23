#pragma once
#include "D3D11RHIResources.h"
#include "D3D11DynamicRHI.h"
#include "PixelFormat.h"
class RHID3D11ViewPort :public RHIViewPort
{
public:
	RHID3D11ViewPort(class D3D11DynamicRHI* InD3DRHI, HWND InWindowHandle, uint32 InSizeX, uint32 InSizeY, EPixelFormat InPreferredPixelFormat);
public:
	/**
	 * ��ȡƽ̨���ؽ�����
	 */
	virtual void* GetNativeSwapChain() const override;
	/**
	 * ��ȡ�󱳻�����
	 */
	virtual void* GetNativeBackBufferTexture() const override;
	/**
	 * ��ȡ�󱳻�������BackBuffer ��RenderTarget
	 */
	virtual void* GetNativeBackBufferRT() const override;

	RHID3D11Texture2D* GetBackBuffer() const { return BackBuffer; }
public:
	D3D11DynamicRHI*								D3DRHI;
	HWND											WindowHandle;
	uint32											ViewSizeX;
	uint32											ViewSizeY;
	EPixelFormat									PreferredPixelFormat;
	Microsoft::WRL::ComPtr < IDXGISwapChain	>		SwapChain;
	RHID3D11Texture2D* BackBuffer;
};

template<>
struct TD3D11ResourceTraits<RHIViewPort>
{
	typedef RHID3D11ViewPort TConcreteType;
};