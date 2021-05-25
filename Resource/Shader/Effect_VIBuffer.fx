matrix	g_matWorld;
matrix	g_matView;
matrix	g_matProjection;

texture	g_texBaseTexture;

float	g_fAlpha = 0;

sampler BaseSampler = sampler_state
{
	texture = g_texBaseTexture;

	minfilter = linear;
	magfilter = linear;
};

///* ���ؽ� ���̵� *///
struct VS_IN
{//VertexShading Input�� ����.

	vector		vPosition : POSITION; 
	float2		vTexUV : TEXCOORD0; 

};

struct VS_OUT
{

	vector		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;


};

VS_OUT		VS_MAIN(VS_IN _In)
{
	VS_OUT	tOut = (VS_OUT)0; //�ʱ�ȭ �ϴ°�

	matrix		matWV, matWVP;


	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProjection);

	tOut.vPosition = mul(vector(_In.vPosition.xyz, 1.f), matWVP);

	tOut.vTexUV = _In.vTexUV;

	return tOut;
}

///* �ȼ� ���̵� *///
struct PS_IN
{//Pixel Shading Input
	float2		vTexUV : TEXCOORD0;
	//float		fAlpha : FOG;
};

struct PS_OUT
{//Pixel Shading Output
	vector		vColor : COLOR0;
};

PS_OUT		PS_MAIN(PS_IN _In)
{
	PS_OUT		tOut = (PS_OUT)0;

	
	tOut.vColor = tex2D(BaseSampler, _In.vTexUV);

	tOut.vColor.a -= g_fAlpha;


	return tOut;
}

technique Default_Device
{
	
	pass	
	{
		alphablendenable = true;	//���� ���� �ϰڴ�.
		srcblend = srcalpha;		//
		destblend = invsrcalpha;	//
		cullmode = none;


		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};
