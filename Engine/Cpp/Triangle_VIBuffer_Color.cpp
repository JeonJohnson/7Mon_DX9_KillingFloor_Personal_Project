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

	// 1. ����Ʈ ���� ����
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

	//2. �����ص� ������� Vertex Buffer ����
	if (FAILED(m_pDX9Device->CreateVertexBuffer(
		m_tVBInfo.m_iVertexCount * m_tVBInfo.m_iVertexMemSize, //�迭�� �� �޸� ������
		0,  //���������� D3DUSAGE_DYNAMIC ���� �μ��� ��������, �������� = ��ƼŬ
		m_tVBInfo.m_iFVF,
		D3DPOOL_MANAGED, //�޸� ���� ��� = ����Ʈ �����ÿ��� _DYNAMIC���� �ؾ���.
		&m_pVB,
		nullptr)))
	{
		return E_FAIL;
	}
	

	assert(L"Triangle_Color's pVB is nullptr"&&m_pVB);

	//3. LPDIRECT3DVERTEXBUFFER9�� ������ ���� ���
	VERTEX_COLOR*	pVertices = nullptr;

	//Lock���� ������ �ϴ°���. �߸��������� ������.
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPos = Vector3(0.f, 1.f, 0.f);
	pVertices[0].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[1].vPos = Vector3(1.f, -1.f, 0.f);
	pVertices[1].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertices[2].vPos = Vector3(-1.f, -1.f, 0.f);
	pVertices[2].uiColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	//Lock���� �����ؼ� �� ������ Unlock���� �ٽ� ����ֱ�.
	m_pVB->Unlock();


	return S_OK;

}

HRESULT Triangle_VIBuffer_Color::Create_IBuffer()
{

	return S_OK;
}


