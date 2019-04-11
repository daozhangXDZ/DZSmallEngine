#include "Basic.hlsli"

// ������ɫ��(2D)
float4 main(VertexPosHTex pIn) : SV_Target
{
    float4 color = gTex.Sample(gSam, pIn.Tex);
    clip(color.a - 0.1f);
    return color;
}