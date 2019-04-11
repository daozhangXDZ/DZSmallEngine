#include "Basic.hlsli"

// ������ɫ��(3D)
float4 main(VertexPosHWNormalTex pIn) : SV_Target
{
	// ��ǰ���вü����Բ�����Ҫ������ؿ��Ա����������
    float4 texColor = gTex.Sample(gSam, pIn.Tex);
    //texColor = gMaterial.Ambient;
    //texColor = gWorld._11_22_33_44;
    //clip(texColor.a - 0.1f);

    //// ��׼��������
    //pIn.NormalW = normalize(pIn.NormalW);

    //// ����ָ���۾�������
    //float3 toEyeW = normalize(gEyePosW - pIn.PosW);

    //// ��ʼ��Ϊ0 
    //float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
    //int i;


    //[unroll]
    //for (i = 0; i < 5; ++i)
    //{
    //    DirectionalLight dirLight = gDirLight[i];
    //    [flatten]
    //    if (gIsReflection)
    //    {
    //        dirLight.Direction = mul(dirLight.Direction, (float3x3) (gReflection));
    //    }
    //    ComputeDirectionalLight(gMaterial, gDirLight[i], pIn.NormalW, toEyeW, A, D, S);
    //    ambient += A;
    //    diffuse += D;
    //    spec += S;
    //}
        
    

    
    //// ����ǰ�ڻ��Ʒ������壬��Ҫ�Թ��ս��з������任
    //PointLight pointLight;
    //[unroll]
    //for (i = 0; i < 5; ++i)
    //{
    //    pointLight = gPointLight[i];
    //    [flatten]
    //    if (gIsReflection)
    //    {
    //        pointLight.Position = mul(float4(pointLight.Position, 1.0f), gReflection).xyz;
    //    }
    //    ComputePointLight(gMaterial, pointLight, pIn.PosW, pIn.NormalW, toEyeW, A, D, S);
    //    ambient += A;
    //    diffuse += D;
    //    spec += S;
    //}
        
    
	
    //SpotLight spotLight;
    //// ����ǰ�ڻ��Ʒ������壬��Ҫ�Թ��ս��з������任
    //[unroll]
    //for (i = 0; i < 5; ++i)
    //{
    //    spotLight = gSpotLight[i];
    //    [flatten]
    //    if (gIsReflection)
    //    {
    //        spotLight.Position = (float3) mul(float4(spotLight.Position, 1.0f), gReflection);
    //        spotLight.Direction = mul(spotLight.Direction, (float3x3) gReflection);
    //    }
    //    ComputeSpotLight(gMaterial, spotLight, pIn.PosW, pIn.NormalW, toEyeW, A, D, S);
    //    ambient += A;
    //    diffuse += D;
    //    spec += S;
    //}
        
    

	
    //float4 litColor = texColor * (ambient + diffuse) + spec;
    //litColor.a = texColor.a * gMaterial.Diffuse.a;
    return texColor;
}
