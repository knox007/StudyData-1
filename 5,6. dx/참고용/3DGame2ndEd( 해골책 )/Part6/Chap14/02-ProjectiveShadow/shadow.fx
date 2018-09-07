// made by newtype@chol.com

// world * view * projection
float4x4	matWV;
float4x4	matProj;
float4x4	matShadowUV;

// 입력정점형식
struct VS_IN
{
	float3	p : POSITION;
	float3	n : NORMAL;
	float2	t : TEXCOORD0;
	float2	s : TEXCOORD1;
};

// 출력정점형식
struct VS_OUT
{
	float4	p : POSITION;
	float4	d : COLOR0;
	float2	t : TEXCOORD0;
	float2	s : TEXCOORD1;
};

// 정점쉐이더
VS_OUT main( VS_IN In )
{
	VS_OUT	o = (VS_OUT)0;
	// matShadowUV : vertex local -> world -> light -> clip space
	// 정점좌표를 텍스처좌표계로 변환하다.
	// 먼저 정점좌표를 광원공간 클리핑 좌표계로 변환 clip space( -1 ~ 1 )
	float4 T = mul( In.p, matShadowUV );

	// 클리핑 좌표계를 텍스처 좌표계로
 	// clip space(-1 ~ 1) -> tex space( 0 ~ 1 )
 	o.s.x = (T.x / 2.0f) + 0.5f;
 	o.s.y = 1.0f - ((T.y / 2.0f) + 0.5f);
// 	o.s = float2( T.x, T.y ) / 2.0f + 0.5f;
	
	// 정점좌표를 카메라공간 클링핑 좌표계로 변환
	float3 P = mul( float4(In.p,1), (float4x3)matWV );
	o.p = mul( float4(P,1), matProj );
	o.d = 1.0f;
	o.t = In.t;
	
	return o;
}
