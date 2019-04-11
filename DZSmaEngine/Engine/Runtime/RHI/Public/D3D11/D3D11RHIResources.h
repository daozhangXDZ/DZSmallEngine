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
class D3D11UniFormBuffer :public RHIUniFormBuffer
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
public:
	UINT bindVSIndex;
	UINT bindPSIndex;
	bool isBindVS = false;
	bool isBindPS = false;
};
typedef D3D11UniFormBuffer* D3D11UniFormBufferRef;

