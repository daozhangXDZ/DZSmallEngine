#include "LightHelper.hlsli"

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
	// 是否反射
    int gIsReflection;
	// 是否折射
    int gIsRefraction;
	// 是否阴影
    int gIsShadowed;
	// 折射率
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

struct VertexPosNormalTex
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float2 Tex : TEXCOORD;
};

struct VertexPosNormalTangentTex
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float4 TangentL : TANGENT;
    float2 Tex : TEXCOORD;
};

struct InstancePosNormalTex
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float2 Tex : TEXCOORD;
    matrix World : World;
    matrix WorldInvTranspose : WorldInvTranspose;
};

struct InstancePosNormalTangentTex
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float4 TangentL : TANGENT;
    float2 Tex : TEXCOORD;
    matrix World : World;
    matrix WorldInvTranspose : WorldInvTranspose;
};

struct VertexPosHWNormalTex
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION; // 在世界中的位置
    float3 NormalW : NORMAL; // 法向量在世界中的方向
    float2 Tex : TEXCOORD;
};

struct VertexPosHWNormalTangentTex
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION; // 在世界中的位置
    float3 NormalW : NORMAL; // 法向量在世界中的方向
    float4 TangentW : TANGENT; // 切线在世界中的方向
    float2 Tex : TEXCOORD;
};





float3 NormalSampleToWorldSpace(float3 normalMapSample,
    float3 unitNormalW,
    float4 tangentW)
{
    // 将读取到法向量中的每个分量从[0, 1]还原到[-1, 1]
    float3 normalT = 2.0f * normalMapSample - 1.0f;

    // 构建位于世界坐标系的切线空间
    float3 N = unitNormalW;
    float3 T = normalize(tangentW.xyz - dot(tangentW.xyz, N) * N); // 施密特正交化
    float3 B = cross(N, T);

    float3x3 TBN = float3x3(T, B, N);

    // 将凹凸法向量从切线空间变换到世界坐标系
    float3 bumpedNormalW = mul(normalT, TBN);

    return bumpedNormalW;
}
