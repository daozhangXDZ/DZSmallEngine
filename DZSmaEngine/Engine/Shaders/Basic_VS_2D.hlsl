#include "Basic.hlsli"

// ¶¥µã×ÅÉ«Æ÷(2D)
VertexPosHTex main(VertexPosTex vIn)
{
    VertexPosHTex vOut;
    vOut.PosH = float4(vIn.PosL, 1.0f);
    vOut.Tex = vIn.Tex;
    return vOut;
}
