// -------------------------------------------------------------
// �ݿ��ݻ籤
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------

float4x4	matWVP;
float4		vecLightDir;	//	��������
float4		vecColor;		//	����*�޽û�
float4		vecEyePos;		//	ī�޶� ��ġ(������ǥ��)
//---------------------------------------------------------------------------
//	�������̴����� �ȼ����̴��� �ѱ�� ������
//---------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4	Pos		:	POSITION;
	float4	Color	:	COLOR0;
	float3	Normal	:	TEXCOORD0;
	float3	Eye		:	TEXCOORD1;
};

//---------------------------------------------------------------------------
//	��鷻��
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
	float3	vecL		=	-vecLightDir;							//	������ǥ�迡���� ��������.
	float3	vecHalf		=	normalize( vecL + normalize(In.Eye));	//	��������.
	float3	vecNor		=	normalize( In.Normal );
	
	return	In.Color		//	Ȯ�걤 + ȯ�汤.
			+ pow( max( 0, dot(vecNor, vecHalf) ), 10 );
}
//---------------------------------------------------------------------------
//	��ũ��
//---------------------------------------------------------------------------
technique	TShader
{
	pass P0
	{
		VertexShader	=	compile vs_3_0	VS();
		PixelShader		=	compile ps_3_0	PS();
	}
}