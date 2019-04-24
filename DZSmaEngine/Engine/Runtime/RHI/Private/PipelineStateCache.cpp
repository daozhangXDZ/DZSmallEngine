#include "PipelineStateCache.h"

/**
 * 设置GS相关状态
 */
void SetComputePipelineState(RHICommandListImmediate* RHICmdList, RHIComputerShader* ComputeShader)
{

}

/**
 * 设置当前管线资源
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
 * 清理管线
 */
void ClearPipelineCache()
{

}