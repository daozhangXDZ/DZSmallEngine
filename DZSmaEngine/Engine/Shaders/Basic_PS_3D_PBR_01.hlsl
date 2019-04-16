#include "Basic.hlsli"

// 像素着色器(3D)
float4 main(VertexPosHWNormalTangentTex pIn) : SV_Target
{
    // 若不使用纹理，则使用默认白色
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

    if (gMaterial.gDiffTextureUsed)
    {
        texColor = gDiffuseMap.Sample(gSam, pIn.Tex);
    }
    if (gMaterial.materialType == 1)
    {
        clip(texColor.a - 0.1f);
    }
    // 标准化法向量
    pIn.NormalW = normalize(pIn.NormalW);

    // 求出顶点指向眼睛的向量，以及顶点与眼睛的距离
    float3 toEyeW = normalize(gEyePosW - pIn.PosW);
    float distToEye = distance(gEyePosW, pIn.PosW);

    // 法线映射
    float3 normalMapSample = float3(0.0f, 0.0f, 1.0f);
    if (gMaterial.gNormalTextureUsed)
    {
        normalMapSample = gNormalMap.Sample(gSam, pIn.Tex).rgb;
    }
    float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pIn.NormalW, pIn.TangentW);

    // 初始化为0 
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
    int i;

    [unroll]
    for (i = 0; i < 1; ++i)
    {
        ComputeDirectionalLight(gMaterial, gDirLight[i], bumpedNormalW, toEyeW, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
    float4 litColor = texColor * (ambient + diffuse) + spec;
    if (gMaterial.materialType == 2)
    {
        litColor.a = texColor.a * gMaterial.Diffuse.a;
    }
    else
    {
        litColor.a = 1.0f;
    }
    return litColor;
}
