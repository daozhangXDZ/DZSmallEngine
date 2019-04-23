#pragma once
#include "D3D11RHIResources.h"
#include "RHIState.h"
#include  <d3d11.h>
#include <wrl/client.h>

///////////////////////////////-------------״̬��Դ----------///////////////////////////////////////////

/// <summary>
/// D3D11��դ��״̬
/// </summary>
struct RHID3D11RasterizerState :public RHIRasterizerState
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
typedef RHID3D11RasterizerState* RHID3D11RasterizerStateRef;
typedef RHID3D11RasterizerState* RHID3D11RasterizerStateParamRef;


/// <summary>
/// D3D11���ģ��״̬
/// </summary>
struct RHID3D11DepthStencilState :public RHIDepthStencilState
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
typedef RHID3D11DepthStencilState* RHID3D11DepthStencilStateRef;
typedef RHID3D11DepthStencilState* RHID3D11DepthStencilStateParamRef;



/// <summary>
/// D3D11��դ��״̬
/// </summary>
struct RHID3D11BlendState :public RHIBlendState
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
typedef RHID3D11BlendState* RHID3D11BlendStateRef;
typedef RHID3D11BlendState* RHID3D11BlendStateParamRef;

/// <summary>
/// �������״̬
/// </summary>
struct RHID3D11SampleState:RHISampleState
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
typedef RHID3D11SampleState* RHID3D11SampleStateRef;
typedef RHID3D11SampleState* RHID3D11SampleStateParamRef;


template<>
struct TD3D11ResourceTraits<RHISampleState>
{
	typedef RHID3D11SampleState TConcreteType;
};
template<>
struct TD3D11ResourceTraits<RHIRasterizerState>
{
	typedef RHID3D11RasterizerState TConcreteType;
};
template<>
struct TD3D11ResourceTraits<RHIDepthStencilState>
{
	typedef RHID3D11DepthStencilState TConcreteType;
};
template<>
struct TD3D11ResourceTraits<RHIBlendState>
{
	typedef RHID3D11BlendState TConcreteType;
};