#pragma once
#include "CoreMinimal.h"
#include "PixelFormat.h"


/** 引用计数类型接口 */
class IRefCountedObject
{
public:
	virtual ~IRefCountedObject() { }
	virtual uint32 AddRef() const = 0;
	virtual uint32 Release() const = 0;
	virtual uint32 GetRefCount() const = 0;
};

class RHIResource
{

};

/////////////////////////////////纹理资源/////////////////////////////////////////
/// <summary>
/// Shader使用的纹理资源
/// </summary>
/// <seealso cref="RHIResource" />
class RHITexture : public RHIResource
{
public:
	RHITexture(uint32 InNumMips,uint32 InNumSamples,EPixelFormat InFormat,FName InTextureName)
		:NumMips(InNumMips),NumSamples(InNumSamples),Format(InFormat),TextureName(InTextureName)
	{

	}

private:
	uint32 NumMips;
	uint32 NumSamples;
	EPixelFormat Format;
	FName TextureName;
};

/// <summary>
/// 2D资源
/// </summary>
/// <seealso cref="RHITexture" />
class RHITexture2D : public RHITexture
{
public:
	RHITexture2D(uint32 InSizeX, uint32 InSizeY, uint32 InNumMips, uint32 InNumSamples, EPixelFormat InFormat, FName InTextureName)
		: RHITexture(InNumMips, InNumSamples, InFormat, InTextureName)
		, SizeX(InSizeX)
		, SizeY(InSizeY)
	{}

	/**
	 * 动态转换
	 * @return 转换后的Texure2D
	 */
	virtual RHITexture2D* GetTexture2D() { return this; }

	/** @return 纹理宽度 */
	uint32 GetSizeX() const { return SizeX; }

	/** @return 纹理高度 */
	uint32 GetSizeY() const { return SizeY; }
private:
	uint32 SizeX;
	uint32 SizeY;
};

typedef RHITexture*              RHITextureParamRef;
typedef RHITexture*				RHITextureRef;

//////////////////////////////////////////////////////////////////////////

/// <summary>
/// 渲染目标抽象
/// </summary>
/// <seealso cref="RHIResource" />
class RHIRenderTarget :public RHIResource
{

};

typedef RHIRenderTarget* RHIRenderTargetRef;
typedef RHIRenderTarget* RHIRenderTargetParamRef;


class RHIDepthTarget :public RHIResource
{

};

typedef RHIDepthTarget* RHIDepthTargetRef;
typedef RHIDepthTarget* RHIDepthTargetParamRef;


//////////////////////////////////////////////////////////////////////////
class RHIVertexShader : public RHIResource {};
class RHIPixelShader : public RHIResource {};
class RHIComputerShader : public RHIResource {};
class RHIVertexInputElement :public RHIResource
{
public:
	void* elementsDesc;
	UINT elementsNumber;

};

class RHIVertexLayout	: public RHIResource 
{
public:
	RHIVertexInputElement* element;
};

typedef RHIVertexShader* RHIVertexShaderRef;
typedef RHIVertexShader* RHIVertexShaderParamRef;

typedef RHIPixelShader* RHIPixelShaderRef;
typedef RHIPixelShader* RHIPixelShaderParamRef;

typedef RHIComputerShader* RHIComputerShaderRef;
typedef RHIComputerShader* RHIComputerShaderParamRef;

typedef RHIVertexInputElement* RHIVertexInputElementRef;
typedef RHIVertexInputElement* RHIVertexInputElementParamRef;

typedef RHIVertexLayout* RHIVertexLayoutRef;
typedef RHIVertexLayout* RHIVertexLayoutParamRef;


//////////////////////////////////////////////////////////////////////////

struct UniFormLayout 
{
	uint32 ConstantBufferSize;
	void*  Resource;
};
typedef UniFormLayout* UniFormLayoutRef;
typedef UniFormLayout* UniFormLayoutParamRef;

class RHIUniFormBuffer : public RHIResource
{
public:
	UniFormLayoutRef Layout;

	RHIVertexShaderRef vertecShader;
	RHIPixelShaderRef pixelShader;
	RHIComputerShaderRef computerShader;
};

typedef RHIUniFormBuffer* RHIUniFormBufferRef;
typedef RHIUniFormBuffer* RHIUniFormBufferParamRef;


//////////////////////////////////////////////////////////////////////////
class RHIShaderResourceView :public RHIResource
{

};
typedef RHIShaderResourceView* RHIShaderResourceViewRef;
typedef RHIShaderResourceView* RHIShaderResourceViewParamRef;


class RHIVertexBuffer : public RHIResource
{

};

class RHIIndexBuffer :public RHIResource
{

};

typedef RHIVertexBuffer* RHIVertexBufferRef;
typedef RHIVertexBuffer* RHIVertexBufferParamRef;

typedef RHIIndexBuffer* RHIIndexBufferRef;
typedef RHIIndexBuffer* RHIIndexBufferParamRef;



////////////////////////////////视口资源抽象//////////////////////////////////////////
class RHIViewPort :public RHIResource
{
public:
	/**
	 * 获取平台本地交换链
	 */
	virtual void* GetNativeSwapChain() const { return nullptr; }
	/**
	 * 获取后背缓冲区
	 */
	virtual void* GetNativeBackBufferTexture() const { return nullptr; }
	/**
	 * 获取后背缓冲区的BackBuffer 的RenderTarget
	 */
	virtual void* GetNativeBackBufferRT() const { return nullptr; }
};

typedef RHIViewPort* RHIViewPortRef;
typedef RHIViewPort* RHIViewPortParamRef;