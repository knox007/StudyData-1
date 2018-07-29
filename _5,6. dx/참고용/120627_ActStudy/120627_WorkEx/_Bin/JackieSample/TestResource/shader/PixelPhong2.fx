// -------------------------------------------------------------
// �ݿ��ݻ籤
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// ��������
// -------------------------------------------------------------

float4x4 matWVP;
float4 vecLightDir;		// ��������
float4 vecColor;		// ����*�޽� ��
float3 vecEyePos;		// ī�޶���ġ(������ǥ��)

// -------------------------------------------------------------
// �������̴����� �ȼ����̴��� �ѱ�� ������
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			:	POSITION;
    float4 Color		:	COLOR0;
    float3 N			:	TEXCOORD0;
    float3 Eye			:	TEXCOORD1;
};
// -------------------------------------------------------------
// ��鷻��
// -------------------------------------------------------------
VS_OUTPUT VS(
      float4 Pos    : POSITION,         // ������ġ��ǥ
      float4 Normal : NORMAL			// ��������
){
	VS_OUTPUT Out = (VS_OUTPUT)0;		// ��µ�����
	
	// ��ǥ��ȯ
	Out.Pos = mul(Pos, matWVP);
	
	// Ȯ�걤+ȯ�汤
	float amb = -vecLightDir.w;			// ȯ�汤�� ����	
	Out.Color = vecColor * max(amb, dot(Normal, -vecLightDir));
	
	// �ݿ��ݻ�� ����
	Out.N   = Normal.xyz;
	Out.Eye = vecEyePos - Pos.xyz;
	
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{   
	float3 L = -vecLightDir;							// ������ǥ�迡���� ��������
	float3 H = normalize(L + normalize(In.Eye));	// ��������
	float3 N = normalize(In.N);
	
    return In.Color									// Ȯ�걤+ȯ�汤
			 + pow(max(0,dot(N, H)), 10);			// �ݿ��ݻ籤
}

// -------------------------------------------------------------
// ��ũ��
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}
