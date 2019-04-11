#pragma  once
#include "CoreMinimal.h"
////////////////////////////////DX渲染状态//////////////////////////////////////////

/// <summary>
/// DX渲染状态，会记录状态的相关信息，用于Debug
/// </summary>
struct RHIBaseState
{
public:
	std::string StateDescName;
};

/// <summary>
/// D3D11光栅化状态
/// </summary>
struct RHIRasterizerState:public RHIBaseState {};
struct RHIDepthStencilState :public RHIBaseState {};
struct RHIBlendState :public RHIBaseState {};
struct RHISampleState :public RHIBaseState {};


typedef RHIRasterizerState* RHIRasterizerStateRef;
typedef RHIRasterizerState* RHIRasterizerStateParamRef;

typedef RHIDepthStencilState* RHIDepthStencilStateRef;
typedef RHIDepthStencilState* RHIDepthStencilStateParamRef;


typedef RHIBlendState* RHIBlendStateRef;
typedef RHIBlendState* RHIBlendStateParamRef;

typedef RHISampleState* RHISampleStateRef;
typedef RHISampleState* RHISampleStateParamRef;



//////////////////////////////////////////////////////////////////////////