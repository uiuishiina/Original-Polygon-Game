//頂点シェーダー入力構造体
struct VSInput
{
    float3 Position : POSITION;
    float4 Color    : COLOR;
};
//頂点シェーダー出力構造体
struct VSOutput
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR;
};
//ピクセルシェーダー入力構造体
struct PSInput
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR;
};

//------  頂点シェーダー出力関数  ------
VSOutput vs(VSInput input)
{
    VSOutput output;
    //次元変換
    output.Position = float4(input.Position, 1.0f);
    //色
    output.Color = input.Color;
    return output;
}

float4 ps(PSInput input) : SV_TARGET
{
    //色
    return input.Color;
}