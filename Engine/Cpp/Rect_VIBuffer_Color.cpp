#include "..\Header\Rect_VIBuffer_Color.h"


Rect_VIBuffer_Color::Rect_VIBuffer_Color()
{
	Initialize();
	//리쏘스 매니저에서 따로 불러올지 여기서 바로 실행시킬지 고민중.
}


Rect_VIBuffer_Color::~Rect_VIBuffer_Color()
{
}

void Rect_VIBuffer_Color::Initialize()
{
	Set_Name(L"Rect_Color");

//1. Vertex 관련 세팅
	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = 4; 
	vTemp.m_iPolyCount = 2;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_COLOR);
	vTemp.m_iFVF = FVF_COLOR;
	Set_VBufferInfo(vTemp);

	//2. VertexBuffer 만들기
	if (FAILED(Create_VBuffer()))
	{
		assert(0 && L"Rect_color Vertex Buffer Create Failed");
	}

	//3.Index Setting
	IBUFFER_INFO iTemp;
	ZeroMemory(&vTemp, sizeof(IBUFFER_INFO));
	iTemp.m_iIndexMemSize = sizeof(INDEX_32);
	iTemp.m_tIndexFMT = D3DFMT_INDEX32;
	Set_IBufferInfo(iTemp);

	//4. InexBuffer만들기
	if (FAILED(Create_IBuffer()))
	{
		assert(0 && L"Rect_color Index Buffer Create Failed");
	}

	//ResourceManager::Get_Instance()->Insert_Resource<VIBuffer,Rect_VIBuffer_Color>()
}

HRESULT Rect_VIBuffer_Color::Create_VBuffer()
{
	if (FAILED(m_pDX9Device->CreateVertexBuffer(
		m_tVBInfo.m_iVertexCount * m_tVBInfo.m_iVertexMemSize,
		0,
		m_tVBInfo.m_iFVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		nullptr)))
	{
		return E_FAIL;
	}
	//이건 VIBuffer에서 해주는게 나을거 같은뎅... ㅎㅎ; 잘못짯당

	VERTEX_COLOR* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPos = Vector3(-1.f, 1.f, 0.f);
	pVertices[0].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[1].vPos = Vector3(1.f, 1.f, 0.f);
	pVertices[1].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[2].vPos = Vector3(1.f, -1.f, 0.f);
	pVertices[2].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	
	pVertices[3].vPos = Vector3(-1.f, -1.f, 0.f);
	pVertices[3].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	m_pVB->Unlock();

	return S_OK;

}

HRESULT Rect_VIBuffer_Color::Create_IBuffer()
{
	if(FAILED(m_pDX9Device->CreateIndexBuffer(
		m_tVBInfo.m_iPolyCount*m_tIBInfo.m_iIndexMemSize, /* 인덱스 배열의 총 메모리 사이즈 */
		0,
		m_tIBInfo.m_tIndexFMT, /* 어떤 포멧인지 */
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr
	)))
	{
		return E_FAIL;
	}
	
	INDEX_32* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	//한 배열에 한 삼각형이라고 생각하면 댐.

	pIndices[0]._1 = 0; //접근이 될란가?
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;


	m_pIB->Unlock();

	return S_OK;

}
