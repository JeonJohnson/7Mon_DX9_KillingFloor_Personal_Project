//���̴� ����.
//�п������� ���̴� 3.0�� ����� ��.
//HLSL�̶�� ���̴��� ��������� �����.
	//=> ���� Ȯ�����α׷� ��ġ���ϸ� ����� ��Ʃ����� �νĸ���.
		//������ ���� ��Ȳ���� ����. �̰ž�.
	//Ȯ���ڴ� .fx || .hpp ��󾲸� ��.

//���̴���?
//������ó�� �׸��ٴ°���.
//�츮�� ��� DX9�� ������ ������������ ���� �׳� ������ �ִ� �������� �����̰�
//���̴��� ���� �츮�� �� �������� �Ը���� �� �ٲٰڴ�. �̸�����.

//������ �����̽���ȯ���� CPU���� �ϰ� �ִµ�
//���̴��� �̰͵��� GPU���� ��ų ���� ����. => ������ ���.
		// ���ʿ� GPU�� CPU���� �Ҽ��� ���� �� ������ ����?
//���� ���ؽ�, �ȼ�� ���������� ȿ���� ���� ���� �ֱ⿡
//�׷������� �� ���� ��� ����. ���� �� ���� ������ ����

//�� �ڵ�� �ϴ� �ΰ��� ������ �Ҳ���.
//1. ���ؽ� ���̵� => �Ž����� �����̽� ��ȯ(��Į~����)�� GPU��
//2. �ȼ� ���̵� => �Ž��� �ؽ����� �ȼ����� ������ ��ȯ�Ҳ���.

matrix	g_matWorld;
matrix	g_matView;
matrix	g_matProjection;

texture	g_texBaseTexture;

float	g_fPower;
//�ߵ��� �츮�� �ƴ� �׷� ������ �ƴ϶�
//��� ���̺���.
//=> �ڱⰡ ���� ���� �����ų� ������ �� ����
	//�׳� Ŭ��Ȥ�� ���������� ������ ���� �� �� ����.

sampler BaseSampler = sampler_state
{//���÷� : �ؽ����� ǰ��, ��¿ɼ� ���� �������ִ� ����ü

	texture = g_texBaseTexture;

	minfilter = linear;
	magfilter = linear;
	//������������ �ؽ��ĸ� ó���ϰڴ�. �̰ž�.
	//¼���� �� �ؽ��� �������� ��° ó���ұ� �ϴ� ��ġ �����̶� ������
};

///* ���ؽ� ���̵� *///
struct VS_IN
{//VertexShading Input�� ����.

	// : => '�ø�ƽ'�̶� �а� �Ӽ��������� ������ �Ѵ�.
		//=> �� �ڴ� �빮�ڷ� ���������.
	//�� vector���� vecPosition�̶�� ������̺���
	// POSITION������ٰ� ����ϰڴ�. �̰ž�.
	vector		vPosition : POSITION; 
	//�Τ�Į ������(INPUT�̴ϱ� ���� View,Projection ��� �޾ƿͼ� ����� �� Output���� ����������.) 
	float2		vTexUV : TEXCOORD0; 
	//�ؽ����0���� 0�� �ִ� ��밡���� (3.0������ 8��) �������� ���ʹ�. �̰ž�.

	//���� Ŭ��or������ ������ �̰ɷ� �޾ƿͼ� ���ڴ�. �̰ž�.
};

struct VS_OUT
{//VertexShading Output�� ����.

	//�Ʊ� VS_IN���� �޾ƿ� �ֵ��� ó���ϰ�
	//�ٽ� Ŭ��or�������� �Ѱ��� ������ ��� ���� ����ü.

	vector		vPosition : POSITION;
	float2		vTexUv : TEXCOORD0;
	//���⼭�� vector�� Dx�� Vector4��.
	//float2�� Dx�� Vector2��...

};

VS_OUT		VS_MAIN(VS_IN _In)
{//������ ���ؽ� ���̵��� �� �Լ���.
	//�츮 C++������ �Լ��� ������ �Ȱ���.
	//�����ְ� �ƿ�ǲ�ְ�.

	VS_OUT	tOut = (VS_OUT)0; //�ʱ�ȭ �ϴ°�

	matrix		matWV, matWVp;
	//'����������'�̴� ���� �ް��ϸ� �� ������ �� ���⺸��
	//��� �ܰ踶�� �ϳ� �� ������ִ°� ���ٰ� �Ͻ�.

	//matWV = World * View Matrix
	matWV = mul(g_matWorld, g_matView);
	//matWVP = WORLD * Veiw * Projection Matrix
	matWVP = mul(matWV, g_matProjection);

	tOut.vPosition = mul(vector(_In.vPosition.xyz, 1.f), matWVP);
	//vector4�ϱ� x,y,z �ְ� ������ w�� 1 �� ���������� ������ �ֵ��� �Ҹ�.

	tOut.vTexUV = _In.vTexUV;

	return tOut;
}

///* �ȼ� ���̵� *///
struct PS_IN
{//Pixel Shading Input
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{//Pixel Shading Output
	vector		vColor : COLOR0;
};

PS_OUT		PS_MAIN(PS_IN _In)
{
	PS_OUT		tOut = (PS_OUT)0;

	tOut.vColor = tex2D(BaseSampler, _In.vTexUV);
	//2���� �ؽ�ó�κ��� UV ���� �ش��ϴ� �ȼ��� ������ �����ϴ� �Լ�, ��ȯŸ���� VECTOR Ÿ��
	//�� �޾ƿ� Texture�� �� UV��ǥ�� �ش��ϴ� �ȼ��� ������ �����ϴ°�.
					
	//���⿡ ���� ���Ұ� �����ָ� ��.

	return Out;
}

technique Default_Device
{//���� ������ ���ؽ� ���̵��� �ȼ� ���̵��� �����ؼ�
	//�����ǰ��� ������.
	//���� ���̵� ���� ������ �� ��ɾ����� ��������]
	//1���� = 1 techniqu�� ����������.
	
	pass	
	{//����� ĸ��ȭ, 
	//PASS�� �̸��� ������� ����� ������� ������ �ε��� ���� 0�� �����ǰ� �ڵ������� �ϳ��� ������
	//Dx9 ����̽����� SetRenderState ó�� ���� ���� �������ִ°�
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		vertexshader = compile vs_3_0 VS_MAIN();	// ������ �Լ� ���
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};
