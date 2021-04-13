#include "..\Header\Line_VIBuffer_Grid.h"



Line_VIBuffer_Grid::Line_VIBuffer_Grid()
{
	Initialize();
}


Line_VIBuffer_Grid::~Line_VIBuffer_Grid()
{
}

void Line_VIBuffer_Grid::Initialize()
{
	m_eKind = VIBUFFER_KIND::VIBuffer_Color;
	m_eDrawType = D3DPT_LINELIST;

	Set_Name(L"Line_Grid");

	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = 6;
	vTemp.m_iPolyCount = 3;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_COLOR);
	vTemp.m_iFVF = FVF_COLOR;
	Set_VBufferInfo(vTemp);

	if (FAILED(Create_VBuffer()))
	{
		assert(0 && L"Rect_color Vertex Buffer Create Failed");
	}

	//IBUFFER_INFO iTemp;
	//ZeroMemory(&vTemp, sizeof(IBUFFER_INFO));
	//iTemp.m_iIndexMemSize = sizeof(INDEX_32_LINE);
	//iTemp.m_tIndexFMT = D3DFMT_INDEX32;
	//Set_IBufferInfo(iTemp);

	//if (FAILED(Create_IBuffer()))
	//{
	//	assert(0 && L"Rect_color Index Buffer Create Failed");
	//}
}

HRESULT Line_VIBuffer_Grid::Create_VBuffer()
{

	if (FAILED(m_pDX9_Device->CreateVertexBuffer(
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

	//x Axis
	pVertices[0].vPos = Vector3(-1000.f, 0.f, 0.f);
	pVertices[0].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	pVertices[1].vPos = Vector3(1000.f, 0.f, 0.f);
	pVertices[1].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	//y Axis
	pVertices[2].vPos = Vector3(0.f, 1000.f, 0.f);
	pVertices[2].uiColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	pVertices[3].vPos = Vector3(0.f, -1000.f, 0.f);
	pVertices[3].uiColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	
	//z Axis
	pVertices[4].vPos = Vector3(0.f, 0.f, 1000.f);
	pVertices[4].uiColor = D3DCOLOR_ARGB(255, 0, 0, 255);
	pVertices[5].vPos = Vector3(0.f, 0.f, -1000.f);
	pVertices[5].uiColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT Line_VIBuffer_Grid::Create_IBuffer()
{
	//if (FAILED(m_pDX9_Device->CreateIndexBuffer(
	//	m_tVBInfo.m_iPolyCount*m_tIBInfo.m_iIndexMemSize, /* 인덱스 배열의 총 메모리 사이즈 */
	//	0,
	//	m_tIBInfo.m_tIndexFMT, /* 어떤 포멧인지 */
	//	D3DPOOL_MANAGED,
	//	&m_pIB,
	//	nullptr
	//)))
	//{
	//	return E_FAIL;
	//}

	//INDEX_32_LINE* pIndices = nullptr;

	//m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	////한 배열에 한 삼각형이라고 생각하면 댐.

	//pIndices[0]._1 = 0; //접근이 될란가?
	//pIndices[0]._2 = 1;

	//pIndices[1]._1 = 2;
	//pIndices[1]._2 = 3;

	//pIndices[2]._1 = 4;
	//pIndices[2]._2 = 5;

	//m_pIB->Unlock();

	return S_OK;
}
