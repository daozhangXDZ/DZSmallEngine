#include "Basic.hlsli"

// 像素着色器(3D)
float4 main(VertexPosHWNormalTex pIn) : SV_Target
{
	// 提前进行裁剪，对不符合要求的像素可以避免后续运算
    float4 texColor = gTex.Sample(gSam, pIn.Tex);
    float4 litColor = texColor + gMaterial.Specular;
    litColor.a = texColor.a;
    return litColor;
}
