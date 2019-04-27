#include "Common/Basic.hlsli"

struct DepthPixelInputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : TEXTURE0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(DepthPixelInputType input) : SV_TARGET
{
    float depthValue;
    float4 color;
    //深度为一个0-1（比例值)
    depthValue = input.depthPosition.z / input.depthPosition.w;
    if (depthValue > 0.95f)
    {
        depthValue = 0.95f;
    }
    if (depthValue < 0.5)
    {
        depthValue = pow(depthValue, 50);
    }
    ////测试代码(消耗了)
    ////（正式非压缩时候为 
    color = float4(depthValue, depthValue, depthValue, 1.0f);
    //if (depthValue > 0.4f)
    //{
    //    color = float4(0.5, 0.0f, 0.0f, 1.0f);
    //}
    //if (depthValue > 0.7f)
    //{
    //    color = float4(1.0, 0.0f, 0.0f, 1.0f);
    //}
    //if (depthValue > 0.8f)
    //{
    //    color = float4(0.0, 1.0f, 0.0f, 1.0f);
    //}
    //if (depthValue > 0.9f)
    //{
    //    color = float4(0.0, 0.0f, 1.0f, 1.0f);
    //}
    return color;
}