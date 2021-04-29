//쉐이더 파일.
//학원에서는 쉐이더 3.0을 사용할 것.
//HLSL이라는 쉐이더용 절차지향언어를 사용함.
	//=> 따로 확장프로그램 설치안하면 비쥬얼 스튜디오는 인식못함.
		//빨간줄 떠도 당황하지 말라. 이거야.
	//확장자는 .fx || .hpp 골라쓰면 됨.

//쉐이더란?
//렌더링처럼 그린다는거임.
//우리가 배운 DX9의 렌더링 파이프라인은 ㄹㅇ 그냥 정해져 있는 고정적인 라인이고
//쉐이더를 쓰면 우리가 그 과정에서 입맛대로 좀 바꾸겠다. 이마리야.

//지금은 스페이스변환등을 CPU에서 하고 있는데
//쉐이더는 이것들을 GPU에게 시킬 수도 있음. => 프레임 향상.
		// 애초에 GPU는 CPU보다 소수점 연산 더 빠른거 알쥐?
//또한 버텍스, 픽셀등에 직접적으로 효과를 넣을 수도 있기에
//그래픽적인 미 또한 향상 가능. 물론 난 아직 몰ㄹ름 ㅋㅋ

//이 코드는 일단 두가지 역할을 할꺼임.
//1. 버텍스 쉐이딩 => 매쉬들의 스페이스 변환(로칼~투영)을 GPU로
//2. 픽셀 쉐이딩 => 매쉬의 텍스쳐의 픽셀들의 색상값을 변환할꺼다.

matrix	g_matWorld;
matrix	g_matView;
matrix	g_matProjection;

texture	g_texBaseTexture;

float	g_fPower;
//야들은 우리가 아는 그런 변수가 아니라
//상수 테이블임.
//=> 자기가 직접 값을 가지거나 수정할 수 없고
	//그냥 클라혹은 엔진에서의 값들을 담을 수 만 있음.

sampler BaseSampler = sampler_state
{//샘플러 : 텍스쳐의 품질, 출력옵션 등을 결정해주는 구조체

	texture = g_texBaseTexture;

	minfilter = linear;
	magfilter = linear;
	//선형보간으로 텍스쳐를 처리하겠다. 이거야.
	//쩌번에 그 텍스쳐 뭉개지면 우째 처리할까 하던 장치 세팅이랑 같은거
};

///* 버텍스 쉐이딩 *///
struct VS_IN
{//VertexShading Input의 약자.

	// : => '시맨틱'이라 읽고 속성지시자의 역할을 한다.
		//=> 이 뒤는 대문자로 적어줘야함.
	//즉 vector형의 vecPosition이라는 상수테이블은
	// POSITION값으루다가 사용하겠다. 이거야.
	vector		vPosition : POSITION; 
	//로ㅡ칼 포지션(INPUT이니까 이제 View,Projection 행렬 받아와서 계산한 뒤 Output으로 내보낼꺼임.) 
	float2		vTexUV : TEXCOORD0; 
	//텍스쿠드0에서 0은 최대 사용가능한 (3.0에서는 8개) 개수까지 쓰것다. 이거야.

	//이제 클라or엔진의 값들을 이걸로 받아와서 쓰겠다. 이거야.
};

struct VS_OUT
{//VertexShading Output의 약자.

	//아까 VS_IN에서 받아온 애들을 처리하고
	//다시 클라or엔진에게 넘겨줄 값들을 들고 있을 구조체.

	vector		vPosition : POSITION;
	float2		vTexUv : TEXCOORD0;
	//여기서의 vector는 Dx의 Vector4임.
	//float2는 Dx의 Vector2고...

};

VS_OUT		VS_MAIN(VS_IN _In)
{//실제로 버텍스 쉐이딩을 할 함수임.
	//우리 C++에서의 함수와 구조는 똑같음.
	//인자있고 아웃풋있고.

	VS_OUT	tOut = (VS_OUT)0; //초기화 하는거

	matrix		matWV, matWVp;
	//'절차지향언어'이다 보니 앵간하면 한 변수를 쭉 쓰기보다
	//계산 단계마다 하나 씩 만들어주는게 좋다고 하심.

	//matWV = World * View Matrix
	matWV = mul(g_matWorld, g_matView);
	//matWVP = WORLD * Veiw * Projection Matrix
	matWVP = mul(matWV, g_matProjection);

	tOut.vPosition = mul(vector(_In.vPosition.xyz, 1.f), matWVP);
	//vector4니까 x,y,z 넣고 마지막 w는 1 즉 방향정보를 가지고 있따는 소리.

	tOut.vTexUV = _In.vTexUV;

	return tOut;
}

///* 픽셀 쉐이딩 *///
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
	//2차원 텍스처로부터 UV 값에 해당하는 픽셀의 색상을 추출하는 함수, 반환타입은 VECTOR 타입
	//즉 받아온 Texture의 각 UV좌표에 해당하는 픽셀의 색상값을 추출하는거.
					
	//여기에 색깔 변할거 적어주면 됨.

	return Out;
}

technique Default_Device
{//현재 결정된 버텍스 쉐이딩과 픽셀 쉐이딩을 구분해서
	//구동되게할 진입점.
	//수업 쉐이딩 파일 구조는 한 기능씩으로 나눌꺼라서]
	//1파일 = 1 techniqu로 나눠질꺼다.
	
	pass	
	{//기능의 캡슐화, 
	//PASS는 이름과 상관없이 선언된 순서대로 위부터 인덱스 값이 0이 지정되고 자동적으로 하나씩 증가함
	//Dx9 디바이스한테 SetRenderState 처럼 렌더 관련 세팅해주는것
		alphablendenable = true;
		srcblend = srcalpha;
		destblend = invsrcalpha;

		vertexshader = compile vs_3_0 VS_MAIN();	// 진입점 함수 명시
		pixelshader = compile ps_3_0 PS_MAIN();
	}

};
