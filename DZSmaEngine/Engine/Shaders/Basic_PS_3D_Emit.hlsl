#include "Basic.hlsli"

// ������ɫ��(3D)
float4 main(VertexPosHWNormalTex pIn) : SV_Target
{
	// ��ǰ���вü����Բ�����Ҫ������ؿ��Ա����������
    float4 texColor = gTex.Sample(gSam, pIn.Tex);
    float4 litColor = texColor + gMaterial.Specular;
    litColor.a = texColor.a;
    return litColor;
}
