// -------------------------------------------------------------
// 반영반사광
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// 전역변수
// -------------------------------------------------------------

float4x4	matWVP;
float4		vecLightDir;	//	광원방향
float4		vecColor;		//	광원*메시색
float4		vecEyePos;		//	카메라 위치(로컬좌표계)
//---------------------------------------------------------------------------
//	정점셰이더에서 픽셀셰이더로 넘기는 데이터
//---------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		:	POSITION;
	float4	Color	:	COLOR0;
	float3	Normal	:	TEXCOORD0;
	float3	Eye		:	TEXCOORD1;
};

//---------------------------------------------------------------------------
//	장면렌더
//---------------------------------------------------------------------------
VS_OUTPUT	VS(
		float4	Pos		:	POSITION,
		float4	Normal	:	NORMAL
		)
		
{
	VS_OUTPUT Out	=	(VS_OUTPUT)0;
	
	Out.Pos		=	mul(Pos, matWVP);
	
	float fAmb	=	-vecLightDir.w;
	Out.Color	=	vecColor * max( fAmb, dot( Normal, -vecLightDir ) );
	
	Out.Normal	=	Normal.xyz;
	Out.Eye		=	vecEyePos - Pos.xyz;
	
	return Out;
}
//---------------------------------------------------------------------------
float4	PS(VS_OUTPUT In)	:	COLOR0
{
	float3	vecL		=	-vecLightDir;							//	로컬좌표계에서의 광원벡터.
	float3	vecHalf		=	normalize( vecL + normalize(In.Eye));	//	하프벡터.
	float3	vecNor		=	normalize( In.Normal );
	
	return	In.Color		//	확산광 + 환경광.
			+ pow( max( 0, dot(vecNor, vecHalf) ), 10 );
}
//---------------------------------------------------------------------------
//	테크닉
//---------------------------------------------------------------------------
technique	TShader
{
	pass P0
	{
		VertexShader	=	compile vs_3_0	VS();
		PixelShader		=	compile ps_3_0	PS();
	}
}