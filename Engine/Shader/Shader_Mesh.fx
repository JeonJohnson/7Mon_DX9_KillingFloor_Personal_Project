//210430금 쉐이더 2번째시간.
//명암 넣기(터레인에서) 근디 나는 터레인 안쓰니께
//바로 매쉬 들어가면서 적용해보자.

//텍스쳐 관련 상수테이블은 똑같음.
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

//쉐이더 들어가기전 '조명'에 대한 간단한 설명
//'빛'과 '재질'이 필요함.

/* 빛 */
//1. 디퓨즈(난반사)
	//=> 빛에 직접 닿는 반사. 빛의 방향과 표면의 형태만 고려하면 됨.
//2. 스펙큘러(정반사)
	//=> 물체에서 빛을 강하게 받는 부분을 특정 각도에서 관찰 할 수 있게 하는 빛.
		//=> 매끈한 물체가 빛을 반사하는 그 느낌 uk what im saying?
	//=> 빛의 방향, 표면의 형태, 관찰자(카메라)의 위치까지 다 알 아야함.
//3. 엠비언트(환경광)
	//=> 다른 표면에 반사되어 반사된 빛을 받는것. 관찰자(카메라)의 위치를 알아야함.

/* 빛, 광원의 종류 */ //D3DLIGHT9 구조체 사용. 
//1. 점광원(Point Light) : 월드 스페이스 내ㅐ에 위치를 가짐. 모든 방향으로 빛 발산.
//2. 방향성 광원(directional Light, 환경광) : 위치는 없지만 지정된 방향으로 평행한 빛 발산.
//3. 스퐅 광원(Spot Light, 손전등) : 손전등처럼 원뿔형태의 빛을 발산함.


/* 재질 */
//1. 디퓨즈 : 표면이 반사하는 나반사광의 양
//2. 스펙큘러 : 표면이 반사하는 정반사광의 양
	//=> 파워 : 정반사광의 날카로운정도(sharpness)지정. 값이 높아질 수록 하이라이트 강조.
//3. 엠비언트 : 표면이 반사하는 환경광의 양
//4. 에미시브 : 발광효과. 표면의 전반적인 컬러를 더함.


//명암에서 필요한 상수 테이블들
/* 빛 */
	//1. 방향
	//2. 디퓨즈 (난반사) 세기
	//3. 스펙큘러 (정반사) 세기
		//=> 관찰자(카메라) 위치
		
	//4. 엠비언트 (환경광)
vector	g_vLightDir;
vector	g_vCamPos;

vector	g_vLightDiffuse;
vector	g_vLightSpecular;
vector	g_vLightAmbient;



/* 머테리얼 */
	//1. 디퓨즈
	//2. 스펙큘러
		//=> power값 : 스펙큘러의 최대ㅡ최소치의 값들을 보정해주기 위해서 씀. 제곱해줘서.
	//3. 엠비언트

vector	g_vMtrlDiffuse;
vector	g_vMtrlSpecular;
float	g_fPower;
vector	g_vMtrlAmbient;


//버텍스쉐이딩
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
	//~ 원래 하던 스페이스 변환.

	//정점의 노말벡터와 빛의 역벡터 외적.
	//WorldNormal -> 정점의 법선 벡터(Vertex의 Normal벡터)를 월드 스페이스로 옮겨주는 역할
	vector vWorldNormal = mul(vector(In.vNormal.xyz, 0.f), g_matWorld); //빛은 방향벡터니까 w값 0으루다가
	//빛의 방향의 역벡터를 구하는 부분.
		//-> 좀 있다가 정점의 법선벡터와 외적해야하는데 방향을 맞춰주기 위해서. 역백터.
	vector vWorldDir = g_vLightDir * -1; //

	float fIntensity = saturate(dot(normalize(vWorldNormal), normalize(vWorldDir)));
	//saturate -> 값을 0~1 사의 값으로 보정해주는 함수.

	tOut.vShade = fIntensity;
	tOut.vShade.a = 1.f;


	//스펙큘러의 세기 값 구하기.
	vector	vReflect = reflect(normalize(g_vLightDir), normalize(vWorldNormal));
	vector  vWorldPos = mul(vector(In.vPosition.xyz, 1.f), g_matWorld);
	//보는 각도에 따라서 달라지기에 Look벡터 만들어야함.
	vector vLook = vWorldPos - g_vCamPos;
	//스페큘러 연산방법 : 퐁(Pong) 쉐이딩
	//1. 반사광과 카메라가 이루는 각도의 코사인 값 구하기
	//2. power값으로 거듭제곱 해서 값 보정해주기.
	tOut.vSpecular = pow(saturate(dot(normalize(vLook) * -1.f, normalize(vReflect))), g_fPower);
	tOut.vSpecular.a = 1.f;

	tOut.vTexUV = In.vTexUV;

	return tOut;
}

/* 픽셀 쉐이딩 */
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

	//난반사 조명 적용
	tOut.vColor = ((In.vShade * vColor) * (g_vLightDiffuse * g_vMtrlDiffuse));
	
	////엠비언트(환경광 적용)
	tOut.vColor += g_vLightAmbient * g_vMtrlAmbient;

	////정반사(스페큘러) 적용
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