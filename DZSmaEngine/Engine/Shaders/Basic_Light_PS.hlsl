#include "Common/Basic.hlsli"
#include "Common/BasicLayout.hlsli"
// ������ɫ��(3D)
float4 main(VertexPosHWNormalTangentTex pIn) : SV_Target
{
    // ����ʹ��������ʹ��Ĭ�ϰ�ɫ
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    [flatten]
    if (gMaterial.gDiffTextureUsed)
    {
        texColor = gDiffuseMap.Sample(gSam, pIn.Tex);
    }
    [flatten]
    if (gMaterial.materialType)
    {
        clip(texColor.a - 0.1f);
    }
    // ��׼��������
    pIn.NormalW = normalize(pIn.NormalW);

    // �������ָ���۾����������Լ��������۾��ľ���
    float3 toEyeW = normalize(gEyePosW - pIn.PosW);
    float distToEye = distance(gEyePosW, pIn.PosW);

    // ����ӳ��
    float3 normalMapSample = float3(0.0f, 0.0f, 1.0f);
    [flatten]
    if (gMaterial.gNormalTextureUsed)
    {
        normalMapSample = gNormalMap.Sample(gSam, pIn.Tex).rgb;
    }
    float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pIn.NormalW, pIn.TangentW);

    // ��ʼ��Ϊ0 
    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
    int i2 = 0;

    
    float bias;
    float2 projectTexCoord;
    float depthValue;
    float lightDepthValue;
    float lightIntensity;
    float4 textureColor;

     //bias = 0.001f;
        //projectTexCoord.x = pIn.lightViewPosition.x / pIn.lightViewPosition.w / 2.0f + 0.5f;
        //projectTexCoord.y = -pIn.lightViewPosition.y / pIn.lightViewPosition.w / 2.0f + 0.5f;
        // [unroll]
        //if ((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
        //{
        //    depthValue = depthMapTexture.Sample(gSam, projectTexCoord).r;
        //    lightDepthValue = pIn.lightViewPosition.z / pIn.lightViewPosition.w;
        //    lightDepthValue = lightDepthValue - bias;
        //     [unroll]
        //    if (lightDepthValue < depthValue)
        //    {
        //        lightIntensity = saturate(dot(pIn.NormalW, pIn.lightPos));
        //        ComputeDirectionalLight(gMaterial, gDirLight[0], bumpedNormalW, toEyeW, A, D, S);
        //        ambient += lightIntensity*A;
        //        diffuse += lightIntensity*D;
        //        spec += lightIntensity*S;
        //    }
        //}
     [unroll]
    for (i2 = 0; i2 < 1; ++i2)
    {
        ComputeDirectionalLight(gMaterial, gDirLight[i2], bumpedNormalW, toEyeW, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
    float4 litColor = texColor * (ambient + diffuse) + spec;
    if (gMaterial.materialType)
    {
        litColor.a = texColor.a * gMaterial.Diffuse.a;
    }
    else
    {
        litColor.a = 1.0f;
    }
    return litColor;
}
