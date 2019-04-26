#include "Common/Basic.hlsli"
#include "Common/BasicLayout.hlsli"


struct UIVertexPosHTex
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
};

// ¶¥µã×ÅÉ«Æ÷(2D)
UIVertexPosHTex main(VertexPosNormalTangentTex vIn)
{
    UIVertexPosHTex vOut;
    vOut.PosH = float4(vIn.PosL, 1.0f);
    vOut.Tex = vIn.Tex;
    return vOut;
}