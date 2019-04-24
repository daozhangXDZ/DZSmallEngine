#pragma once
#include "RHISources.h"
#include "RHICommandList.h"

/**
 * 设置GS相关状态
 */
extern void SetComputePipelineState(RHICommandListImmediate* RHICmdList, RHIComputerShader* ComputeShader);

/**
 * 设置当前管线资源
 */
extern void SetGraphicsPipelineState(RHICommandListImmediate* RHICmdList,
	const RHIGraphicsPipelineStateInitializer& Initializer
);

/**
 * 清理管线
 */
extern void ClearPipelineCache();