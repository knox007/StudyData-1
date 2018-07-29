//---------------------------------------------------------------------------
// ºí¸°Æþ (¹Ý¿µ¹Ý»ç±¤)
//---------------------------------------------------------------------------
float4x4	matWVP;
float4		vecLightDir;
float4		vecColor;
float3		vecEyePos;
//---------------------------------------------------------------------------
struct	VS_OUT
{
	float4	Pos		:POSITION;
	float4	Color	:COLOR0;
};
//---------------------------------------------------------------------------
VS_OUT VS( 
	float4 Pos		:	POSITION,
	float4 Normal	:	NORMAL
	)
{
	VS_OUT Out = (VS_OUT)0;
		
	Out.Pos	= mul(Pos, matWVP);	
	
	float fAmb = -vecLightDir.w;
	
	float3 vecNormal = Normal.xyz;
	float3 vecLight = -vecLightDir;
	float3 vecEye = normalize(vecEyePos - Pos.xyz);

	float3 vecHalf = normalize( vecLight + vecEye );	// ÇÏÇÁº¤ÅÍ
	Out.Color = vecColor 
				* max(fAmb, dot(vecNormal, -vecLightDir)) 
				+ pow(max(0, dot(vecNormal,vecHalf)), 10);
	
	return Out;	
}
//---------------------------------------------------------------------------
float4 PS(VS_OUT In) : COLOR
{
	return In.Color;
}
//---------------------------------------------------------------------------
technique TShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
//---------------------------------------------------------------------------
//	EOF