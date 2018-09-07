// -------------------------------------------------------------
// 반영반사광
// 
// Copyright (c) 2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// 전역변수
// -------------------------------------------------------------

float4x4 matWVP;
float4 vecLightDir;		// 광원방향
float4 vecColor;		// 광원*메시 색
float3 vecEyePos;		// 카메라위치(로컬좌표계)

// -------------------------------------------------------------
// 정점셰이더에서 픽셀셰이더로 넘기는 데이터
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			:	POSITION;
    float4 Color		:	COLOR0;
    float3 N			:	TEXCOORD0;
    float3 Eye			:	TEXCOORD1;
};
// -------------------------------------------------------------
// 장면렌더
// -------------------------------------------------------------
VS_OUTPUT VS(
      float4 Pos    : POSITION,         // 로컬위치좌표
      float4 Normal : NORMAL			// 법선벡터
){
	VS_OUTPUT Out = (VS_OUTPUT)0;		// 출력데이터
	
	// 좌표변환
	Out.Pos = mul(Pos, matWVP);
	
	// 확산광+환경광
	float amb = -vecLightDir.w;			// 환경광의 강도	
	Out.Color = vecColor * max(amb, dot(Normal, -vecLightDir));
	
	// 반영반사용 벡터
	Out.N   = Normal.xyz;
	Out.Eye = vecEyePos - Pos.xyz;
	
	return Out;
}
// -------------------------------------------------------------
float4 PS(VS_OUTPUT In) : COLOR
{   
	float3 L = -vecLightDir;							// 로컬좌표계에서의 광원벡터
	float3 H = normalize(L + normalize(In.Eye));	// 하프벡터
	float3 N = normalize(In.N);
	
    return In.Color									// 확산광+환경광
			 + pow(max(0,dot(N, H)), 10);			// 반영반사광
}

// -------------------------------------------------------------
// 테크닉
// -------------------------------------------------------------
technique TShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader  = compile ps_3_0 PS();
    }
}
