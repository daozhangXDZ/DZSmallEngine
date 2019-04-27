#include "../Common/LightHelper.hlsli"

Texture2D gDiffuseMap : register(t0);
Texture2D gNormalMap : register(t1);
TextureCube gTexCube : register(t2);
SamplerState gSam : register(s0);




cbuffer CBChangesEveryDrawing : register(b0)
{
   
    float4x4 gWorld;
    float4x4 gWorldInvTranspose;
    Material gMaterial;
}

cbuffer CBDrawingStates : register(b1)
{
	// �Ƿ���
    int gIsReflection;
	// �Ƿ�����
    int gIsRefraction;
	// �Ƿ���Ӱ
    int gIsShadowed;
	// ������
    float eta;
}

cbuffer CBChangesEveryFrame : register(b2)
{
    float4x4 gView;
    float3 gEyePosW;
}

cbuffer CBChangesOnResize : register(b3)
{
    float4x4 gProj;
    float2   gCamaraN_F;
}

cbuffer CBChangesRarely : register(b4)
{
    float4x4 gReflection;
    float4x4 gShadow;
    float4x4 gRefShadow;
    DirectionalLight gDirLight[5];
    PointLight gPointLight[5];
    SpotLight gSpotLight[5];
}




float3 NormalSampleToWorldSpace(float3 normalMapSample,
    float3 unitNormalW,
    float4 tangentW)
{
    // ����ȡ���������е�ÿ��������[0, 1]��ԭ��[-1, 1]
    float3 normalT = 2.0f * normalMapSample - 1.0f;

    // ����λ����������ϵ�����߿ռ�
    float3 N = unitNormalW;
    float3 T = normalize(tangentW.xyz - dot(tangentW.xyz, N) * N); // ʩ����������
    float3 B = cross(N, T);

    float3x3 TBN = float3x3(T, B, N);

    // ����͹�����������߿ռ�任����������ϵ
    float3 bumpedNormalW = mul(normalT, TBN);

    return bumpedNormalW;
}
