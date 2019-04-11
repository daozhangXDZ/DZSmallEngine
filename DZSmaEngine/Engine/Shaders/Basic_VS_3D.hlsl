#include "Basic.hlsli"

// 顶点着色器(3D)
VertexPosHWNormalTex main(VertexPosNormalTex vIn)
{
    VertexPosHWNormalTex vOut;
    
    matrix viewProj = mul(gView, gProj);
    float4 posW = mul(float4(vIn.PosL, 1.0f), gWorld);
    float3 normalW = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);
    //// 若当前在绘制反射物体，先进行反射操作
    //[flatten]
    //if (gIsReflection)
    //{
    //    posW = mul(posW, gReflection);
    //    normalW = mul(normalW, (float3x3) gReflection);
    //}
    //// 若当前在绘制阴影，先进行投影操作
    //[flatten]
    //if (gIsShadow)
    //{
    //    posW = (gIsReflection ? mul(posW, gRefShadow) : mul(posW, gShadow));
    //}

    //float4 posH = mul(float4(vIn.PosL, 1.0f), gMatALL);
    //float4 posW = mul(float4(vIn.PosL, 1.0f), gWorld);
    //float3 normalW = mul(vIn.NormalL, (float3x3) gWorldInvTranspose);
    //vOut.PosH = float4(vIn.PosL, 1.0f);
    //vOut.PosH = float4(gWorld._11_22_33, 1.0f);
    //vOut.PosH = mul(float4(vIn.PosL, 1.0f), gWorld);
    //vOut.PosH = float4(vIn.PosL, 1.0f);
    //vOut.PosH = float4(0.0f, 0.0f, 0.0f, 1.0f);
    vOut.PosH = mul(posW, viewProj);
    vOut.PosW = posW.xyz;
    vOut.NormalW = normalW;
    vOut.Tex = vIn.Tex;
    return vOut;
}