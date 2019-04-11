#include "LightHelper.hlsli"

Texture2D gTex : register(t0);
SamplerState gSam : register(s0);


cbuffer CBChangesEveryDrawing : register(b0)
{
    float4x4 gWorld;
    float4x4 gWorldInvTranspose;
    Material gMaterial;
}

cbuffer CBDrawingStates : register(b1)
{
    int gIsReflection;
    int gIsShadow;
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

struct VertexPosTex
{
    float3 PosL : POSITION;
    float2 Tex : TEXCOORD;
};

struct VertexPosHWNormalTex
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION; // 在世界中的位置
    float3 NormalW : NORMAL; // 法向量在世界中的方向
    float2 Tex : TEXCOORD;
};

struct VertexPosHTex
{
    float4 PosH : SV_POSITION;
    float2 Tex : TEXCOORD;
};






