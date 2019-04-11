#pragma  once
#include "CoreMinimal.h"
////////////////////////////////DX��Ⱦ״̬//////////////////////////////////////////

/// <summary>
/// DX��Ⱦ״̬�����¼״̬�������Ϣ������Debug
/// </summary>
struct RHIBaseState
{
public:
	std::string StateDescName;
};

/// <summary>
/// D3D11��դ��״̬
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