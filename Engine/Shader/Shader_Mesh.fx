//210430�� ���̴� 2��°�ð�.
//��� �ֱ�(�ͷ��ο���) �ٵ� ���� �ͷ��� �Ⱦ��ϲ�
//�ٷ� �Ž� ���鼭 �����غ���.

//�ؽ��� ���� ������̺��� �Ȱ���.
matrix		g_matWorld;
matrix		g_matView;
matrix		g_matProjection;

texture		g_texBaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_texBaseTexture;

	minfilter = linear;
	magfilter = linear;
};

//���̴� ������ '����'�� ���� ������ ����
//'��'�� '����'�� �ʿ���.

/* �� */
//1. ��ǻ��(���ݻ�)
	//=> ���� ���� ��� �ݻ�. ���� ����� ǥ���� ���¸� ����ϸ� ��.
//2. ����ŧ��(���ݻ�)
	//=> ��ü���� ���� ���ϰ� �޴� �κ��� Ư�� �������� ���� �� �� �ְ� �ϴ� ��.
		//=> �Ų��� ��ü�� ���� �ݻ��ϴ� �� ���� uk what im saying?
	//=> ���� ����, ǥ���� ����, ������(ī�޶�)�� ��ġ���� �� �� �ƾ���.
//3. �����Ʈ(ȯ�汤)
	//=> �ٸ� ǥ�鿡 �ݻ�Ǿ� �ݻ�� ���� �޴°�. ������(ī�޶�)�� ��ġ�� �˾ƾ���.

/* ��, ������ ���� */ //D3DLIGHT9 ����ü ���. 
//1. ������(Point Light) : ���� �����̽� ������ ��ġ�� ����. ��� �������� �� �߻�.
//2. ���⼺ ����(directional Light, ȯ�汤) : ��ġ�� ������ ������ �������� ������ �� �߻�.
//3. ���j ����(Spot Light, ������) : ������ó�� ���������� ���� �߻���.


/* ���� */
//1. ��ǻ�� : ǥ���� �ݻ��ϴ� ���ݻ籤�� ��
//2. ����ŧ�� : ǥ���� �ݻ��ϴ� ���ݻ籤�� ��
	//=> �Ŀ� : ���ݻ籤�� ��ī�ο�����(sharpness)����. ���� ������ ���� ���̶���Ʈ ����.
//3. �����Ʈ : ǥ���� �ݻ��ϴ� ȯ�汤�� ��
//4. ���̽ú� : �߱�ȿ��. ǥ���� �������� �÷��� ����.


//��Ͽ��� �ʿ��� ��� ���̺��
/* �� */
	//1. ����
	//2. ��ǻ�� (���ݻ�) ����
	//3. ����ŧ�� (���ݻ�) ����
		//=> ������(ī�޶�) ��ġ
		
	//4. �����Ʈ (ȯ�汤)
vector	g_vLightDir;
vector	g_vCamPos;

vector	g_vLightDiffuse;
vector	g_vLightSpecular;
vector	g_vLightAmbient;



/* ���׸��� */
	//1. ��ǻ��
	//2. ����ŧ��
		//=> power�� : ����ŧ���� �ִ���ּ�ġ�� ������ �������ֱ� ���ؼ� ��. �������༭.
	//3. �����Ʈ

vector	g_vMtrlDiffuse;
vector	g_vMtrlSpecular;
float	g_fPower;
vector	g_vMtrlAmbient;


//���ؽ����̵�
struct VS_IN
{
	vector	vPosition	: POSITION;
	vector	vNormal		: NORMAL;
	float2	vTexUV		:	TEXCOORD0;

};

struct VS_OUT
{
	vector	vPosition	: POSITION;
	vector	vShade		: COLOR0;
	vector	vSpecular	: COLOR1;
	float2	vTexUV		: TEXCOORD0;
};

VS_OUT		VS_MAIN(VS_IN	In)
{
	VS_OUT		tOut = (VS_OUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProjection);

	tOut.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	//~ ���� �ϴ� �����̽� ��ȯ.

	//������ �븻���Ϳ� ���� ������ ����.
	//WorldNormal -> ������ ���� ����(Vertex�� Normal����)�� ���� �����̽��� �Ű��ִ� ����
	vector vWorldNormal = mul(vector(In.vNormal.xyz, 0.f), g_matWorld); //���� ���⺤�ʹϱ� w�� 0����ٰ�
	//���� ������ �����͸� ���ϴ� �κ�.
		//-> �� �ִٰ� ������ �������Ϳ� �����ؾ��ϴµ� ������ �����ֱ� ���ؼ�. ������.
	vector vWorldDir = g_vLightDir * -1; //

	float fIntensity = saturate(dot(normalize(vWorldNormal), normalize(vWorldDir)));
	//saturate -> ���� 0~1 ���� ������ �������ִ� �Լ�.

	tOut.vShade = fIntensity;
	tOut.vShade.a = 1.f;


	//����ŧ���� ���� �� ���ϱ�.
	vector	vReflect = reflect(normalize(g_vLightDir), normalize(vWorldNormal));
	vector  vWorldPos = mul(vector(In.vPosition.xyz, 1.f), g_matWorld);
	//���� ������ ���� �޶����⿡ Look���� ��������.
	vector vLook = vWorldPos - g_vCamPos;
	//����ŧ�� ������ : ��(Pong) ���̵�
	//1. �ݻ籤�� ī�޶� �̷�� ������ �ڻ��� �� ���ϱ�
	//2. power������ �ŵ����� �ؼ� �� �������ֱ�.
	tOut.vSpecular = pow(saturate(dot(normalize(vLook) * -1.f, normalize(vReflect))), g_fPower);
	tOut.vSpecular.a = 1.f;

	tOut.vTexUV = In.vTexUV;

	return tOut;
}

/* �ȼ� ���̵� */
struct PS_IN
{
	vector		vShade		:	COLOR0;
	vector		vSpecular	:	COLOR1;
	float2		vTexUV		:	TEXCOORD0;
};

struct PS_OUT
{
	vector		vColor		:	COLOR0;

};

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		tOut = (PS_OUT)0;

	vector vColor = tex2D(BaseSampler, In.vTexUV);

	//���ݻ� ���� ����
	tOut.vColor = ((In.vShade * vColor) * (g_vLightDiffuse * g_vMtrlDiffuse));
	
	////�����Ʈ(ȯ�汤 ����)
	tOut.vColor += g_vLightAmbient * g_vMtrlAmbient;

	////���ݻ�(����ŧ��) ����
	tOut.vColor += In.vSpecular * (g_vLightSpecular * g_vMtrlSpecular);

		//+ (g_vLightAmbient * g_vMtrlAmbient) 
		//+ (In.vSpecular * (g_vLightSpecular * g_vMtrlSpecular));


	return tOut;
}

technique Default_Device
{
	pass
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};