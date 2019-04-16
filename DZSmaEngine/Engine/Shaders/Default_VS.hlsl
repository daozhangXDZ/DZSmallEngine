#include "Basic.hlsli"

// ������ɫ��(3D)
// ������ɫ��
VertexPosHWNormalTex main(VertexPosNormalTex vIn)
{
    VertexPosHWNormalTex vOut;
    
    matrix viewProj = mul(gView, gProj);
    vector posW = mul(float4(vIn.PosL, 1.0f), gWorld);

    vOut.PosW = posW.xyz;
    vOut.PosH = mul(posW, viewProj);
    vOut.NormalW = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);
    vOut.Tex = vIn.Tex;
    return vOut;
}