
// �����
struct DirectionalLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float3 Direction;
    float Pad;
};

// ���
struct PointLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;

    float3 Position;
    float Range;

    float3 Att;
    float Pad;
};

// �۹��
struct SpotLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;

    float3 Position;
    float Range;

    float3 Direction;
    float Spot;

    float3 Att;
    float Pad;
};

// ����������
struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular; // w = SpecPower
    float4 Reflect;
};



void ComputeDirectionalLight(Material mat, DirectionalLight L,
	float3 normal, float3 toEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec)
{
	// ��ʼ�����
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// �����������䷽���෴
    float3 lightVec = -L.Direction;

	// ��ӻ�����
    ambient = mat.Ambient * L.Ambient;

	// ����������;����
    float diffuseFactor = dot(lightVec, normal);

	// չ�������⶯̬��֧
	[flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }
}


void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	// ��ʼ�����
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// �ӱ��浽��Դ������
    float3 lightVec = L.Position - pos;

	// ���浽���ߵľ���
    float d = length(lightVec);

	// �ƹⷶΧ����
    if (d > L.Range)
        return;

	// ��׼��������
    lightVec /= d;

	// ���������
    ambient = mat.Ambient * L.Ambient;

	// ������;������
    float diffuseFactor = dot(lightVec, normal);

	// չ���Ա��⶯̬��֧
	[flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }

	// ���˥��
    float att = 1.0f / dot(L.Att, float3(1.0f, d, d * d));

    diffuse *= att;
    spec *= att;
}


void ComputeSpotLight(Material mat, SpotLight L, float3 pos, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	// ��ʼ�����
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// // �ӱ��浽��Դ������
    float3 lightVec = L.Position - pos;

    // ���浽��Դ�ľ���
    float d = length(lightVec);

	// ��Χ����
    if (d > L.Range)
        return;

	// ��׼��������
    lightVec /= d;

	// ���㻷���ⲿ��
    ambient = mat.Ambient * L.Ambient;


    // �����������;��淴��ⲿ��
    float diffuseFactor = dot(lightVec, normal);

	// չ���Ա��⶯̬��֧
	[flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);

        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }

	// ���������Ӻ�˥��ϵ��
    float spot = pow(max(dot(-lightVec, L.Direction), 0.0f), L.Spot);
    float att = spot / dot(L.Att, float3(1.0f, d, d * d));

    ambient *= spot;
    diffuse *= att;
    spec *= att;
}