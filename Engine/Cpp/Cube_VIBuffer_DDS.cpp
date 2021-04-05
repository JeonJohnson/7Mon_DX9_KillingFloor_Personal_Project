#include "Cube_VIBuffer_DDS.h"



Cube_VIBuffer_DDS::Cube_VIBuffer_DDS()
{
	Initialize();
}


Cube_VIBuffer_DDS::~Cube_VIBuffer_DDS()
{
}

void Cube_VIBuffer_DDS::Initialize()
{
	m_eKind = VIBUFFER_KIND::VIBuffer_Textrue;

	Set_Name(L"Cube_Texture");

	//1. Vertex Setting
	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = 8;
	vTemp.m_iPolyCount = 12;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_DDS);
	vTemp.m_iFVF = FVF_DDS;
	Set_VBufferInfo(vTemp);
	//UV란? = 텍스쳐 좌표계
	//U = x , V = x
	//0부터 1까지의 수치를 가짐(비율)
	//좌측 상단이 (0,0), 우측 하단이 (1,1);
	//텍스쳐를 입힐때 각 정점에서 Texture 이미지 파일에서 어느 부분을 사용할껀지 매치 시킨다...?
	// 이런 의미로 이해하면 될 듯


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


}

HRESULT Cube_VIBuffer_DDS::Create_VBuffer()
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
	//이건 VIBuffer에서 해주는게 나을거 같은뎅... ㅎㅎ; 몰르겠당 ㅎㅎ

	VERTEX_DDS* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	
	//태쌤코드에서 CubeTexture은 스카이박스띄우는거임.
	//그래서 일반적인 이미지 파일이 아니라 dds(directx Texture)파일인데 3차원 텍스쳐 파일이라서
	//그냥 UV좌표에다가 정점좌표 떄려박는거.
	//3차원 dds 텍스쳐 쓴다고해도 
	//만약 정점의 길이가 1을 벗어나버릴 경우에는 nomalize해서 박아줘야함.
	//나는 스카이박스 VIBuffer은 따로 만들꺼고 얘는 단순 이미지 텍스쳐 쓸꺼라서 제대로 UV입히자.

	//가까운(내[카메라] 기준) 좌상단
	pVertices[0].vPos = Vector3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vUV = pVertices[0].vPos;

	//가까운쪽 우 상단
	pVertices[1].vPos = Vector3(0.5f, 0.5f,-0.5f);
	pVertices[1].vUV = pVertices[1].vPos;

	//가까운쪽 우 하단
	pVertices[2].vPos = Vector3(0.5f, -0.5f,-0.5f);
	pVertices[2].vUV = pVertices[2].vPos;

	//가까운쪽 좌 하단
	pVertices[3].vPos = Vector3(-0.5f,-0.5f,-0.5f);
	pVertices[3].vUV = pVertices[3].vPos;

	//먼쪽 좌 상단
	pVertices[4].vPos = Vector3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vUV = pVertices[4].vPos;

	//먼쪽 우 상단
	pVertices[5].vPos = Vector3(0.5f, 0.5f, 0.5f);
	pVertices[5].vUV = pVertices[5].vPos;

	//먼쪽 우 하단
	pVertices[6].vPos = Vector3(0.5f,-0.5f, 0.5f);
	pVertices[6].vUV = pVertices[6].vPos;

	//먼쪽 좌 하단
	pVertices[7].vPos = Vector3(-0.5f,-0.5f, 0.5f);
	pVertices[7].vUV = pVertices[7].vPos;

	m_pVB->Unlock();

	return S_OK;
}

HRESULT Cube_VIBuffer_DDS::Create_IBuffer()
{

	if (FAILED(m_pDX9_Device->CreateIndexBuffer(
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

	// +x (우측면)
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 5;
	pIndices[0]._3 = 6;

	pIndices[1]._1 = 1;
	pIndices[1]._2 = 6;
	pIndices[1]._3 = 2;

	// -x (좌측면)
	pIndices[2]._1 = 4;
	pIndices[2]._2 = 0;
	pIndices[2]._3 = 3;

	pIndices[3]._1 = 4;
	pIndices[3]._2 = 3;
	pIndices[3]._3 = 7;

	// +y (윗면)
	pIndices[4]._1 = 4;
	pIndices[4]._2 = 5;
	pIndices[4]._3 = 1;

	pIndices[5]._1 = 4;
	pIndices[5]._2 = 1;
	pIndices[5]._3 = 0;

	// -y (아랫면)
	pIndices[6]._1 = 6;
	pIndices[6]._2 = 7;
	pIndices[6]._3 = 3;

	pIndices[7]._1 = 6;
	pIndices[7]._2 = 3;
	pIndices[7]._3 = 2;

	// +z (먼쪽 면)
	pIndices[8]._1 = 5;
	pIndices[8]._2 = 4;
	pIndices[8]._3 = 7;

	pIndices[9]._1 = 5;
	pIndices[9]._2 = 7;
	pIndices[9]._3 = 6;

	// -z (가까운 면)
	pIndices[10]._1 = 0;
	pIndices[10]._2 = 1;
	pIndices[10]._3 = 2;

	pIndices[11]._1 = 0;
	pIndices[11]._2 = 2;
	pIndices[11]._3 = 3;

	m_pIB->Unlock();

	return S_OK;

}

void Cube_VIBuffer_DDS::Set_Texture(Texture * _pTexture)
{
	assert(L"Texture is nullptr" && _pTexture);

	m_pTexture = _pTexture;
}

HRESULT Cube_VIBuffer_DDS::Render_Texture(int _iNum)
{
	if (FAILED(m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))))
	{
		return E_FAIL;
	}

	return S_OK;
}
 