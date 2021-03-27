#include "..\Header\Triangle_VIBuffer_Color.h"



Triangle_VIBuffer_Color::Triangle_VIBuffer_Color()
{
	Initialize();
}


Triangle_VIBuffer_Color::~Triangle_VIBuffer_Color()
{
}

void Triangle_VIBuffer_Color::Initialize()
{
	Set_Name(L"Tri_Color");

	// 1. 디폴트 변수 세팅
	VBUFFER_INFO Temp;
	ZeroMemory(&Temp, sizeof(VBUFFER_INFO));

	Temp.m_iVertexCount = 3;
	Temp.m_iPolyCount = 1;
	Temp.m_iVertexMemSize = sizeof(VERTEX_COLOR);
	Temp.m_iFVF = FVF_COLOR;

	Set_VBufferInfo(Temp);

	if (Create_VBuffer() == E_FAIL)
	{
		//MsgBox(L"Error", L"TriangleColor VertexBuffer Create Failed");
	}
	//
}

HRESULT Triangle_VIBuffer_Color::Create_VBuffer()
{
	/*HRESULT CreateVertexBuffer(
		UINT Length,
		DWORD Usage,
		DWORD FVF,
		D3DPOOL Pool,
		IDirect3DVertexBuffer9** ppVertexBuffer,
		HANDLE* pHandle
	);*/

	//2. 지정해둔 변수들로 Vertex Buffer 세팅
	if (FAILED(m_pDX9Device->CreateVertexBuffer(
		m_tVBInfo.m_iVertexCount * m_tVBInfo.m_iVertexMemSize, //배열의 총 메모리 사이즈
		0,  //동적버퍼인 D3DUSAGE_DYNAMIC 외의 인수는 정적버퍼, 동적버퍼 = 파티클
		m_tVBInfo.m_iFVF,
		D3DPOOL_MANAGED, //메모리 저장 방식 = 디폴트 동적시에는 _DYNAMIC으로 해야함.
		&m_pVB,
		nullptr)))
	{
		return E_FAIL;
	}
	

	assert(L"Triangle_Color's pVB is nullptr"&&m_pVB);

	//3. LPDIRECT3DVERTEXBUFFER9에 접근해 정점 찍기
	VERTEX_COLOR*	pVertices = nullptr;

	//Lock으로 접근을 하는거임. 잘못이해하지 말도록.
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPos = Vector3(0.f, 1.f, 0.f);
	pVertices[0].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[1].vPos = Vector3(1.f, -1.f, 0.f);
	pVertices[1].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[2].vPos = Vector3(-1.f, -1.f, 0.f);
	pVertices[2].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	//Lock으로 접근해서 다 썻으면 Unlock으로 다시 잠궈주기.
	m_pVB->Unlock();


	return S_OK;

}

HRESULT Triangle_VIBuffer_Color::Create_IBuffer()
{

	return S_OK;
}


