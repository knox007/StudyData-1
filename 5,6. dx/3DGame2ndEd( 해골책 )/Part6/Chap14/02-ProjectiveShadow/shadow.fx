// made by newtype@chol.com

// world * view * projection
float4x4	matWV;
float4x4	matProj;
float4x4	matShadowUV;

// �Է���������
struct VS_IN
{
	float3	p : POSITION;
	float3	n : NORMAL;
	float2	t : TEXCOORD0;
	float2	s : TEXCOORD1;
};

// �����������
struct VS_OUT
{
	float4	p : POSITION;
	float4	d : COLOR0;
	float2	t : TEXCOORD0;
	float2	s : TEXCOORD1;
};

// �������̴�
VS_OUT main( VS_IN In )
{
	VS_OUT	o = (VS_OUT)0;
	// matShadowUV : vertex local -> world -> light -> clip space
	// ������ǥ�� �ؽ�ó��ǥ��� ��ȯ�ϴ�.
	// ���� ������ǥ�� �������� Ŭ���� ��ǥ��� ��ȯ clip space( -1 ~ 1 )
	float4 T = mul( In.p, matShadowUV );

	// Ŭ���� ��ǥ�踦 �ؽ�ó ��ǥ���
 	// clip space(-1 ~ 1) -> tex space( 0 ~ 1 )
 	o.s.x = (T.x / 2.0f) + 0.5f;
 	o.s.y = 1.0f - ((T.y / 2.0f) + 0.5f);
// 	o.s = float2( T.x, T.y ) / 2.0f + 0.5f;
	
	// ������ǥ�� ī�޶���� Ŭ���� ��ǥ��� ��ȯ
	float3 P = mul( float4(In.p,1), (float4x3)matWV );
	o.p = mul( float4(P,1), matProj );
	o.d = 1.0f;
	o.t = In.t;
	
	return o;
}
