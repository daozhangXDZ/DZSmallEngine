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
     // 提前进行裁剪，对不符合要求的像素可以避免后续运算
    if (gMaterial.materialType == 1 || gMaterial.materialType == 2)
    {
        clip(texColor.a - 0.1f);
    }
    float4 litColor = texColor;
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
