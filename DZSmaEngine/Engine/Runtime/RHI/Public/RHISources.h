#pragma once
#include "CoreMinimal.h"
#include "PixelFormat.h"
#include "RHIState.h"

/**
 * 绘制方式
 */
enum PrimitiveTopology
{
	TRIANGLELIST = 0,
};
/** 引用计数类型接口 */
class IRefCountedObject
{
public:
	virtual ~IRefCountedObject() { }
	virtual uint32 AddRef() const = 0;
	virtual uint32 Release() const = 0;
	virtual uint32 GetRefCount() const = 0;
};

/**
 * 渲染资源基类（完成计数）
 */
class RHIResource
{
public:
	FORCEINLINE uint32 AddRef() const
	{
		int32 NewValue = NumRefs.Increment();
		return uint32(NewValue);
	}
	FORCEINLINE uint32 Release() const
	{
		int32 NewValue = NumRefs.Decrement();
		if (NewValue == 0)
		{
			delete this;
		}
		return uint32(NewValue);
	}
	FORCEINLINE uint32 GetRefCount() const
	{
		int32 CurrentValue = NumRefs.GetValue();
		return uint32(CurrentValue);
	}

private:
	mutable FThreadSafeCounter NumRefs;
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

	virtual void* GetNativeShaderResourceView() const
	{
		// Override this in derived classes to expose access to the native texture resource
		return nullptr;
	}

	virtual void* GetNativeResource() const
	{
		// Override this in derived classes to expose access to the native texture resource
		return nullptr;
	}

	virtual void* GetTextureBaseRHI()
	{
		// Override this in derived classes to expose access to the native texture resource
		return nullptr;
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

typedef RHITexture2D*              RHITexture2DParamRef;
typedef RHITexture2D*				RHITexture2DRef;

//////////////////////////////////////////////////////////////////////////

/// <summary>
/// 渲染目标视图
/// </summary>
/// <seealso cref="RHIResource" />
class RHIRenderTarget :public RHIResource
{
public:
	RHIRenderTarget() :
		Texture(NULL),
		MipIndex(0)
	{

	}

	RHIRenderTarget(const RHIRenderTarget& Other) :
		Texture(Other.Texture),
		MipIndex(Other.MipIndex)
	{

	}

	explicit RHIRenderTarget(RHITextureParamRef InTexture) :
		Texture(InTexture),
		MipIndex(0)
	{

	}


public:
	RHITextureParamRef Texture;
	uint32 MipIndex;
};

typedef RHIRenderTarget* RHIRenderTargetRef;
typedef RHIRenderTarget* RHIRenderTargetParamRef;



/**
 * 深度视图
 */
class RHIDepthTarget :public RHIResource
{
public:
	RHITextureParamRef Texture;
public:
	RHIDepthTarget() :
		Texture(NULL)
	{

	}

	RHIDepthTarget(const RHIRenderTarget& Other) :
		Texture(Other.Texture)
	{

	}

	explicit RHIDepthTarget(RHITextureParamRef InTexture) :
		Texture(InTexture)
	{

	}
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


/**
 * 作为一个渲染资源的组合结构供给Pipeline使用
 * TODO：后面加入将CS，GS，HS
 */
struct RHIBoundShaderStateInput
{
	/**
	 * 顶点布局
	 */
	RHIVertexLayoutRef mVertexLayout;
	RHIVertexShaderRef mVertexShader;
	RHIPixelShaderRef  mPixelShader;
public:
	RHIBoundShaderStateInput() :mVertexShader(nullptr), mPixelShader(nullptr), mVertexLayout(nullptr)
	{

	}

	RHIBoundShaderStateInput(RHIVertexShaderParamRef InVertexShader, RHIPixelShaderParamRef InPixelShader,RHIVertexLayoutParamRef InVertexLayout)
		:mVertexShader(InVertexShader), mPixelShader(InPixelShader),mVertexLayout(InVertexLayout)
	{

	}
};

/**
 * 渲染管线初始化结构
 */
class RHIGraphicsPipelineStateInitializer
{
public:
	RHIBoundShaderStateInput		BoundShaderState;
	RHIBlendStateParamRef			BlendState;
	RHIRasterizerStateParamRef		RasterizerState;
	RHIDepthStencilStateParamRef	DepthStencilState;
	/**
	 * 是否带有输出的渲染目标
	 */
	uint32							RenderTargetsEnabled;
	EPixelFormat					RenderTargetFormat;
	PrimitiveTopology				mPrimitiveToPology;
};