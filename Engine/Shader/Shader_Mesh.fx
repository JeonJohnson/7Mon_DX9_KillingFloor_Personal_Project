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

//명암에서 필요한 상수 테이블들
/* 빛 */
	//1. 방향
	//2. 디퓨즈 (난반사)
	//3. 스펙큘러 (정반사)
		//=> power값 : 스펙큘러의 최대ㅡ최소치의 값들을 보정해주기 위해서 씀. 제곱해줘서.
	//4. 엠비언트
	

/* 머테리얼 */
	//1. 디퓨즈
	//2. 스펙큘러
	//3. 엠비언트

