#include "Common/Basic.hlsli"
#include "Common/BasicLayout.hlsli"

struct DepthPixelInputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : TEXTURE0;
};

DepthPixelInputType main(VertexPosNormalTangentTex vIn)
{
    DepthPixelInputType output;

    matrix viewProj = mul(gView, gProj);
    vector posW = mul(float4(vIn.PosL, 1.0f), gWorld);
    output.position = mul(posW, viewProj);
    output.depthPosition = output.position;
    return output;
}