#include "Common/Basic.hlsli"

struct DepthPixelInputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : TEXTURE0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(DepthPixelInputType input) : SV_TARGET
{
    float depthValue;
    float4 color;
    depthValue = input.depthPosition.z / gClip_N_F.y;
    //depthValue = input.depthPosition.z / input.depthPosition.w;
    color = float4(depthValue, depthValue, depthValue, 1.0f);
    return color;
}