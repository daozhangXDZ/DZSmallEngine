#include "Common/Basic.hlsli"
#include "Common/BasicLayout.hlsli"
// 像素着色器(3D)
float4 main(VertexPosHWNormalTangentTex pIn) : SV_Target
{
    // 若不使用纹理，则使用默认白色
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    [flatten]
    if (gMaterial.gDiffTextureUsed)
    {
        texColor = gDiffuseMap.Sample(gSam, pIn.Tex);
    }

    //float3 normalMapSample = float3(0.0f, 0.0f, 1.0f);
    //[flatten]
    //if (gMaterial.gNormalTextureUsed)
    //{
    //    normalMapSample = gNormalMap.Sample(gSam, pIn.Tex).rgb;
    //}
    //texColor.rgb = normalMapSample;

    if (gMaterial.materialType)
    {
        texColor.a = texColor.a * gMaterial.Diffuse.a;
    }
    else
    {
        texColor.a = 1.0f;
    }
    return texColor;
}
