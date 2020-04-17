cbuffer ConstantBuffer: register(b0)
{
	float4x4 mwpMatrix;
}

Texture2D g_texture : register(t0);
SamplerState g_sampler: register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PSInput VSMain(float4 position : POSITION, float4 diffuse : DIFFUSE, float4 normal : NORMAL, float4 texcoord: TEXCOORD)
{
	PSInput result;


	result.position = mul(mwpMatrix, position);
	result.color = diffuse;
	result.uv = texcoord.xy;

	return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
	return input.color * g_texture.Sample(g_sampler, input.uv);
}
