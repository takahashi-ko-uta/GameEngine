#include "Particle.hlsli"

VSOutput main(float4 pos : POSITION,float scale : TEXCOORD)
{
	VSOutput output; // ピクセルシェーダーに渡す値
	output.pos = pos;		//頂点座標
	output.scale = scale;	//スケール
	/*output.svpos = mul(mat, pos);
	output.normal = normal;
	output.uv = uv;*/
	return output;
}