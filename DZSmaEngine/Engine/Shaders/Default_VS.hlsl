#include "Basic.hlsli"

// ¶¥µã×ÅÉ«Æ÷(3D)
VertexPosHWNormalTex main(VertexPosNormalTex vIn)
{
    VertexPosHWNormalTex vOut;
    
    matrix viewProj = mul(gView, gProj);
    float4 posW = mul(float4(vIn.PosL, 1.0f), gWorld);
    float3 normalW = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);

    vOut.PosH = mul(posW, viewProj);
    vOut.PosW = posW.xyz;
    vOut.NormalW = normalW;
    vOut.Tex = vIn.Tex;
    return vOut;
}