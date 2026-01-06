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
//カメラコンスタントバッファ
cbuffer ConstantBuffer : register(b0)
{
    matrix view_;
    matrix projection_;
}
//ポリゴン
cbuffer ConstantBuffer : register(b1)
{
    matrix world_;
    float4 color_;
}

//------  頂点シェーダー出力関数  ------
VSOutput vs(VSInput input)
{
    VSOutput output;
    //次元変換
    float4 pos = float4(input.Position, 1.0f);
    pos = mul(pos, world_);
    pos = mul(pos, view_);
    pos = mul(pos, projection_);
    output.Position = pos;
    
    //色
    output.Color = input.Color;
    return output;
}

float4 ps(VSOutput input) : SV_TARGET
{
    //色
    return input.Color * color_;
}