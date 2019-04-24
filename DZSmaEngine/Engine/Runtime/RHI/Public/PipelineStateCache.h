#pragma once
#include "RHISources.h"
#include "RHICommandList.h"

/**
 * ����GS���״̬
 */
extern void SetComputePipelineState(RHICommandListImmediate* RHICmdList, RHIComputerShader* ComputeShader);

/**
 * ���õ�ǰ������Դ
 */
extern void SetGraphicsPipelineState(RHICommandListImmediate* RHICmdList,
	const RHIGraphicsPipelineStateInitializer& Initializer
);

/**
 * �������
 */
extern void ClearPipelineCache();