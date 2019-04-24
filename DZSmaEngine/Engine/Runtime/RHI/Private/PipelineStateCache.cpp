#include "PipelineStateCache.h"

/**
 * ����GS���״̬
 */
void SetComputePipelineState(RHICommandListImmediate* RHICmdList, RHIComputerShader* ComputeShader)
{

}

/**
 * ���õ�ǰ������Դ
 */
void SetGraphicsPipelineState(RHICommandListImmediate* RHICmdList,
	const RHIGraphicsPipelineStateInitializer& Initializer
)
{
	RHISetRasterizerState(Initializer.RasterizerState);
	RHISetDepthState(Initializer.DepthStencilState);
	RHISetBlendState(Initializer.BlendState);
	RHIOMPInputLayout(Initializer.BoundShaderState.mVertexLayout);
	RHIOMVSShader(Initializer.BoundShaderState.mVertexShader);
	RHIOMPSShader(Initializer.BoundShaderState.mPixelShader);
}

/**
 * �������
 */
void ClearPipelineCache()
{

}