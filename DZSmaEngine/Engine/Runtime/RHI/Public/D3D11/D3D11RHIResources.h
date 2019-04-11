#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include "CoreMinimal.h"
using namespace DirectX;


class D3D11RenderResource 
{

};

//////////////////////////////////--------------资源--------------////////////////////////////////////////

class D3D11ShaderResourceViewRes : public D3D11RenderResource
{
public:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResView;
};

typedef D3D11ShaderResourceViewRes* D3D11ShaderResourceViewResParamRef;
//////////////////////////////////--------------着色器资源--------------///////////////////////////////////////


/**
 * DX11着色器
 */
class D3D11ShaderRes:public D3D11RenderResource
{
public:
	D3D11ShaderRes() {};
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
typedef D3D11ShaderRes* D3D11ShaderResParamRef;



/**
 * DX11顶点着色器
 */
class D3D11VertexShaderRes:public D3D11ShaderRes
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

typedef D3D11VertexShaderRes* D3D11VertexShaderResParamRef;


/**
 * DX11像素着色器
 */
class D3D11PixelShaderRes :public D3D11ShaderRes
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

typedef D3D11PixelShaderRes* D3D11PixelShaderResParamRef;




//////////////////////////////////---------顶点数据布局资源------------////////////////////////////////////////
class D3D11InputLayoutRes :public D3D11RenderResource
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
typedef D3D11InputLayoutRes* D3D11InputLayoutResParamRef;





//////////////////////////////////---------渲染目标资源------------////////////////////////////////////////
/// <summary>
///  
/// </summary>
/// <seealso cref="D3D11RenderResource" />
class D3D11RenderTargetResource :public D3D11RenderResource
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

typedef D3D11RenderTargetResource* D3D11RHIRenderTargetParamRef;


//////////////////////////////////---------深度目标资源------------////////////////////////////////////////
class D3D11DepthResource :public D3D11RenderResource
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

typedef D3D11DepthResource* D3D11DepthResourceParamRef;


///////////////////////////////-------------状态资源----------///////////////////////////////////////////


/// <summary>
/// DX渲染状态，会记录状态的相关信息，用于Debug
/// </summary>
struct D3D11BaseStateRes
{
public:
	std::string StateDescName;

};

/// <summary>
/// D3D11光栅化状态
/// </summary>
struct D3D11RasterizerStateRes :public D3D11BaseStateRes
{
public:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	mRasterizerState;
	void** GetStateNativeAddress()
	{
		return reinterpret_cast<void**>(mRasterizerState.GetAddressOf());
	}
	void* GetStateAddress()
	{
		return reinterpret_cast<void*>(mRasterizerState.Get());
	}
};
typedef D3D11RasterizerStateRes* D3D11RasterizerStateResParamRef;



/// <summary>
/// D3D11深度模版状态
/// </summary>
struct D3D11DepthStencilStateRes :public D3D11BaseStateRes
{
public:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDdepthStencilState;
	void** GetStateNativeAddress()
	{
		return reinterpret_cast<void**>(mDdepthStencilState.GetAddressOf());
	}
	void* GetStateAddress()
	{
		return reinterpret_cast<void*>(mDdepthStencilState.Get());
	}
};
typedef D3D11DepthStencilStateRes* D3D11DepthStencilStateResParamRef;



/// <summary>
/// D3D11光栅化状态
/// </summary>
struct D3D11BlendStateRes :public D3D11BaseStateRes
{
public:
	Microsoft::WRL::ComPtr<ID3D11BlendState>	mBlendState;
	void** GetStateNativeAddress()
	{
		return reinterpret_cast<void**>(mBlendState.GetAddressOf());
	}
	void* GetStateAddress()
	{
		return reinterpret_cast<void*>(mBlendState.Get());
	}
};
typedef D3D11BlendStateRes* D3D11BlendStateResParamRef;



//////////////////////////////////---------纹理采样-----------////////////////////////////////////////

/// <summary>
/// 纹理采样状态
/// </summary>
struct D3D11TextureSampleState
{
public:
	std::string SampleName;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
	void** GetStateNativeAddress()
	{
		return reinterpret_cast<void**>(samplerState.GetAddressOf());
	}
	void* GetStateAddress() const
	{
		return reinterpret_cast<void*>(samplerState.Get());
	}
};
typedef D3D11TextureSampleState* D3D11TextureSampleStateParamRef;


/////////////////////////////////---------顶点布局-----------/////////////////////////////////////////
class D3DInputElementRes :public D3D11RenderResource
{
public:
	D3D11_INPUT_ELEMENT_DESC* elementsDesc;
	UINT elementsNumber;
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
typedef D3DInputElementRes* D3DInputElementResParamRef;

/**
 * 绘制方式
 */
enum PrimitiveTopology
{
	TRIANGLELIST = 0,
};

//////////////////////////////////缓璁去资源////////////////////////////////////////
class D3D11VertexBufferRes:public D3D11RenderResource
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
typedef D3D11VertexBufferRes* D3D11VertexBufferResParamRef;


class D3D11IndexBufferRes :public D3D11RenderResource
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
	UINT bufferSize = 0;

public:
	D3D11IndexBufferRes() {}


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
typedef D3D11IndexBufferRes* D3D11IndexBufferResParamRef;


/**
 * 
 */
class D3D11ConstanBufferRes :public D3D11RenderResource
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
public:
	UINT bindVSIndex;
	UINT bindPSIndex;
	bool isBindVS = false;
	bool isBindPS = false;
};
typedef D3D11ConstanBufferRes* D3D11ConstanBufferResParamRef;

enum D3D11ShaderType
{
	VertexShader = 0,
	PixelShader = 1,
};