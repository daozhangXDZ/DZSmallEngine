#include "Common/Basic.hlsli"
#include "Common/BasicLayout.hlsli"

struct UIVertexPosHTex
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
};
// ÏñËØ×ÅÉ«Æ÷(2D)
float4 main(UIVertexPosHTex pIn) : SV_Target
{
   // return float4(1.0,0.0,0.0,1.0);
    float4 tColor = gDiffuseMap.Sample(gSam, pIn.Tex);
    tColor.a = 1.0;
    return tColor;
}