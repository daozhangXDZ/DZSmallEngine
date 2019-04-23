#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "CoreMinimal.h"
#include "RHISources.h"
using namespace DirectX;

//////////////////////////////////--------------资源--------------////////////////////////////////////////

class RHID3D11ShaderResourceView : public RHIShaderResourceView
{
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResView;
};
typedef RHID3D11ShaderResourceView* RHID3D11ShaderResViewRef;
typedef RHID3D11ShaderResourceView* RHID3D11ShaderResViewParamRef;
//////////////////////////////////--------------着色器资源--------------///////////////////////////////////////


/**
 * DX11着色器
 */
class D3D11Shader:public RHIResource
{
public:
	D3D11Shader() {};
	void * GetResBlob()
	{
		return mShaderBuffer.Get();
	}
	void ** GetResBlobNativeAddressOf()
	{
		return reinterpret_cast<void**>(mShaderBuffer.GetAddressOf());
	}
	FString ShaderName;
public:
	Microsoft::WRL::ComPtr<ID3DBlob> mShaderBuffer;
};
typedef D3D11Shader* D3D11ShaderParamRef;



/**
 * DX11顶点着色器
 */
class RHID3D11VertexShader:public D3D11Shader,public RHIVertexShader
{
public:
	ID3D11VertexShader * GetShader()
	{
		return mShader.Get();
	}
	void** GetNativeAddress()
	{
		return reinterpret_cast<void**>(mShader.GetAddressOf());
	}
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mShader;
};

typedef RHID3D11VertexShader* RHID3D11VertexShaderRef;
typedef RHID3D11VertexShader* RHID3D11VertexShaderParamRef;


/**
 * DX11像素着色器
 */
class RHID3D11PixelShader :public D3D11Shader, public RHIPixelShader
{
public:
	ID3D11PixelShader * GetShader()
	{
		return mShader.Get();
	}
	void** GetNativeAddress()
	{
		return reinterpret_cast<void**>(mShader.GetAddressOf());
	}
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mShader;
	
};

typedef RHID3D11PixelShader* RHID3D11PixelShaderRef;
typedef RHID3D11PixelShader* RHID3D11PixelShaderParamRef;



//////////////////////////////////---------顶点数据布局资源------------////////////////////////////////////////
class RHID3D1VertexInputLayout :public RHIVertexLayout
{
public:
	ID3D11InputLayout * GetInput()
	{
		return mInput.Get();
	}
	void ** GetNativeAddressOff()
	{
		return  reinterpret_cast<void**>(mInput.GetAddressOf());
	}
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInput;
};
typedef RHID3D1VertexInputLayout* RHID3D11InputLayoutRef;
typedef RHID3D1VertexInputLayout* RHID3D11InputLayoutParamRef;





//////////////////////////////////---------渲染目标资源------------////////////////////////////////////////
/// <summary>
///  
/// </summary>
/// <seealso cref="RHIResource" />
class RHID3D11RenderTarget :public RHIRenderTarget
{
public:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView	>	md3d11RenderTargetView;
public:
	void** GetTextureNativeAddress()
	{
		return 	reinterpret_cast<void**>(backBuffer.GetAddressOf());
	}

	ID3D11Resource* GetBackBuffer()
	{
		return 	backBuffer.Get();
	}

	ID3D11RenderTargetView** GetRTNativeAddress()
	{
		return md3d11RenderTargetView.GetAddressOf();
	}

};
typedef RHID3D11RenderTarget* RHID3D11RenderTargetRef;
typedef RHID3D11RenderTarget* RHID3D11RenderTargetParamRef;


//////////////////////////////////---------深度目标资源------------////////////////////////////////////////
class RHID3D11DepthTarget :public RHIDepthTarget
{
public:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthTexture;
	Microsoft::WRL::ComPtr< ID3D11DepthStencilView	>	md3d11DepthStencilView;
public:


	ID3D11Resource* GetDepthBuffer()
	{
		return 	DepthTexture.Get();
	}

	void** GetTextureNativeAddress()
	{
		return 	reinterpret_cast<void**>(DepthTexture.GetAddressOf());
	}

	ID3D11DepthStencilView* GetDepthView()
	{
		return md3d11DepthStencilView.Get();
	}

	void** GetDepthViewNativeAddress()
	{
		return reinterpret_cast<void**>(md3d11DepthStencilView.GetAddressOf());
	}

public:
	int MipLevels;
	int width;
	int height;
};

typedef RHID3D11DepthTarget* RHID3D11DepthTargetRef;
typedef RHID3D11DepthTarget* RHID3D11DepthTagtetParamRef;


//////////////////////////////////////////////////////////////////////////




/////////////////////////////////---------顶点布局-----------/////////////////////////////////////////
class D3DInputElement :public RHIVertexInputElement
{
public:
	void* GetNative()
	{
		return reinterpret_cast<void*>(input.Get());
	}

	void** GetNativeAddressOff()
	{
		return reinterpret_cast<void**>(input.GetAddressOf());
	}
public:
	Microsoft::WRL::ComPtr < ID3D11InputLayout > input;
};
typedef D3DInputElement* D3DInputElementParamRef;

/**
 * 绘制方式
 */
enum PrimitiveTopology
{
	TRIANGLELIST = 0,
};

//////////////////////////////////缓璁去资源////////////////////////////////////////
class RHID3D11VertexBuffer:public RHIVertexBuffer
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	std::shared_ptr<UINT> stride;
	UINT bufferSize = 0;

public:
	ID3D11Buffer* Get()const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return this->bufferSize;
	}

	void SetBufferSize(UINT size)
	{
		this->bufferSize = size;
	}

	const UINT Stride() const
	{
		return *this->stride.get();
	}

	const UINT * StridePtr() const
	{
		return this->stride.get();
	}

	void Reset()
	{
		buffer.Reset();
	}
};
typedef RHID3D11VertexBuffer* RHID3D11VertexBufferRef;
typedef RHID3D11VertexBuffer* RHID3D11VertexBufferParamRef;


class RHID3D11IndexBuffer :public RHIIndexBuffer
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT bufferSize = 0;

public:
	RHID3D11IndexBuffer() {}


	ID3D11Buffer* Get() const
	{
		return buffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return buffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return this->bufferSize;
	}
};
typedef RHID3D11IndexBuffer* RHID3D11IndexBufferRef;
typedef RHID3D11IndexBuffer* RHID3D11IndexBufferParamRef;


/**
 * 
 */
class RHID3D11UniFormBuffer :public RHIUniFormBuffer
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
public:
	UINT bindVSIndex;
	UINT bindPSIndex;
	bool isBindVS = false;
	bool isBindPS = false;
};
typedef RHID3D11UniFormBuffer* RHID3D11UniFormBufferRef;



//////////////////////////////////////-----------纹理资源-----------////////////////////////////////////

class D3D11BaseShaderResource : public IRefCountedObject
{

};
/** Texture base class. */
class D3D11TextureBase:public D3D11BaseShaderResource
{
public:
	D3D11TextureBase(class D3D11DynamicRHI* InD3DRHI, ID3D11Resource* InRes, ID3D11ShaderResourceView* InShaderResourceView,
		ID3D11RenderTargetView* InRT, ID3D11DepthStencilView* InDepthview
		)
		:D3DRHI(InD3DRHI),Resource(InRes),ShaderResourceView(InShaderResourceView)
		,RenderTargetView(InRT),DepthStencilView(InDepthview)
	{

	}

	ID3D11RenderTargetView* GetRenderTargetView() const
	{
		return RenderTargetView.Get();
	}

	ID3D11DepthStencilView* GetDepthStencilView() const
	{
		return DepthStencilView.Get();
	}

	ID3D11Resource* GetResource() const { return Resource.Get(); }
	ID3D11ShaderResourceView* GetShaderResourceView() const { return ShaderResourceView.Get(); }
	D3D11BaseShaderResource* GetBaseShaderResource() const { return BaseShaderResource; }


protected:
	D3D11DynamicRHI* D3DRHI;

	Microsoft::WRL::ComPtr<ID3D11Resource> Resource;

	/** A shader resource view of the texture. */
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderResourceView;

	/** A render targetable view of the texture. */
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;

	/** A depth-stencil targetable view of the texture. */
	Microsoft::WRL::ComPtr <ID3D11DepthStencilView> DepthStencilView;

	/** Pointer to the base shader resource. Usually the object itself, but not for texture references. */
	D3D11BaseShaderResource* BaseShaderResource;
};


class D3D11BaseTexture2D : public RHITexture2D
{
public:
	D3D11BaseTexture2D(uint32 InSizeX, uint32 InSizeY, uint32 InSizeZ, uint32 InNumMips, uint32 InNumSamples, EPixelFormat InFormat, FName InTextureName)
		: RHITexture2D(InSizeX, InSizeY, InNumMips, InNumSamples, InFormat,InTextureName)
	{}
	uint32 GetSizeZ() const { return 0; }
};




template<typename BaseResourceType>
class TD3D11Texture2D : public BaseResourceType, public D3D11TextureBase
{
public:
	TD3D11Texture2D(class D3D11DynamicRHI* InD3DRHI,
		ID3D11Texture2D* InResource,
		ID3D11ShaderResourceView* InShaderResourceView,
		ID3D11RenderTargetView* InRT, ID3D11DepthStencilView* InDepthview,
		uint32 InSizeX, uint32 InSizeY, uint32 InNumMips, uint32 InNumSamples, EPixelFormat InFormat, FName InTextureName)
		:
		BaseResourceType(InSizeX, InSizeY, 0,InNumMips, InNumSamples, InFormat, InTextureName),
		D3D11TextureBase(InD3DRHI,InResource,InShaderResourceView,InRT,InDepthview)
	{

	}

	ID3D11Texture2D* GetResource() const { return (ID3D11Texture2D*)D3D11TextureBase::GetResource(); }
	/** FRHITexture override.  See FRHITexture::GetNativeResource() */
	virtual void* GetNativeResource() const override final
	{
		return GetResource();
	}
	virtual void* GetNativeShaderResourceView() const override final
	{
		return GetShaderResourceView();
	}
	virtual void* GetTextureBaseRHI() override final
	{
		return static_cast<D3D11TextureBase*>(this);
	}

	// IRefCountedObject interface.
	virtual uint32 AddRef() const
	{
		return RHIResource::AddRef();
	}
	virtual uint32 Release() const
	{
		return RHIResource::Release();
	}
	virtual uint32 GetRefCount() const
	{
		return RHIResource::GetRefCount();
	}
};

typedef TD3D11Texture2D<RHITexture>              RHID3D11Texture;
typedef TD3D11Texture2D<D3D11BaseTexture2D>      RHID3D11Texture2D;


/////////////////////////////////---------------转换-------------------------/////////////////////////////////////////

/** Given a pointer to a RHI texture that was created by the D3D11 RHI, returns a pointer to the FD3D11TextureBase it encapsulates. */
FORCEINLINE D3D11TextureBase* GetD3D11TextureFromRHITexture(RHITexture* Texture)
{
	if (!Texture)
	{
		return NULL;
	}
	D3D11TextureBase* Result((D3D11TextureBase*)Texture->GetTextureBaseRHI());
	return Result;
}



template<class T>
struct TD3D11ResourceTraits
{
};

template<>
struct TD3D11ResourceTraits<RHIVertexInputElement>
{
	typedef D3DInputElement TConcreteType;
};

template<>
struct TD3D11ResourceTraits<RHIVertexShader>
{
	typedef RHID3D11VertexShader TConcreteType;
};


template<>
struct TD3D11ResourceTraits<RHIPixelShader>
{
	typedef RHID3D11PixelShader TConcreteType;
};


template<>
struct TD3D11ResourceTraits<RHITexture>
{
	typedef RHID3D11Texture TConcreteType;
};
template<>
struct TD3D11ResourceTraits<RHITexture2D>
{
	typedef RHID3D11Texture2D TConcreteType;
};

template<>
struct TD3D11ResourceTraits<RHIUniFormBuffer>
{
	typedef RHID3D11UniFormBuffer TConcreteType;
};
template<>
struct TD3D11ResourceTraits<RHIIndexBuffer>
{
	typedef RHID3D11IndexBuffer TConcreteType;
};

template<>
struct TD3D11ResourceTraits<RHIVertexBuffer>
{
	typedef RHID3D11VertexBuffer TConcreteType;
};

template<>
struct TD3D11ResourceTraits<RHIShaderResourceView>
{
	typedef RHID3D11ShaderResourceView TConcreteType;
};


