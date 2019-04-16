#include "Basic.hlsli"

// ������ɫ��(3D)
float4 main(VertexPosHWNormalTangentTex pIn) : SV_Target
{
    // ����ʹ��������ʹ��Ĭ�ϰ�ɫ
    float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

    if (gMaterial.gDiffTextureUsed)
    {
        texColor = gDiffuseMap.Sample(gSam, pIn.Tex);
    }
     // ��ǰ���вü����Բ�����Ҫ������ؿ��Ա����������
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
