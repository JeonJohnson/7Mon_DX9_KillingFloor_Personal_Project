#include "Cube_VIBuffer_Texture.h"



Cube_VIBuffer_Texture::Cube_VIBuffer_Texture()
{
	Initialize();
}


Cube_VIBuffer_Texture::~Cube_VIBuffer_Texture()
{
}

void Cube_VIBuffer_Texture::Initialize()
{
	Set_Name(L"Cube_Texture");

	//1. Vertex Setting
	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = 8;
	vTemp.m_iPolyCount = 12;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_TEXTURE);
	vTemp.m_iFVF = FVF_TEXTURE;
	Set_VBufferInfo(vTemp);
	//UV��? = �ؽ��� ��ǥ��
	//U = x , V = x
	//0���� 1������ ��ġ�� ����(����)
	//���� ����� (0,0), ���� �ϴ��� (1,1);
	//�ؽ��ĸ� ������ �� �������� Texture �̹��� ���Ͽ��� ��� �κ��� ����Ҳ��� ��ġ ��Ų��...?
	// �̷� �ǹ̷� �����ϸ� �� ��


	//2. VertexBuffer �����
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

	//4. InexBuffer�����
	if (FAILED(Create_IBuffer()))
	{
		assert(0 && L"Rect_color Index Buffer Create Failed");
	}


}

HRESULT Cube_VIBuffer_Texture::Create_VBuffer()
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
	//�̰� VIBuffer���� ���ִ°� ������ ������... ����; �����ڴ� ����

	VERTEX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	
	//�½��ڵ忡�� CubeTexture�� ��ī�̹ڽ����°���.
	//�׷��� �Ϲ����� �̹��� ������ �ƴ϶� dds(directx Texture)�����ε� 3���� �ؽ��� �����̶�
	//�׳� UV��ǥ���ٰ� ������ǥ �����ڴ°�.
	//3���� dds �ؽ��� ���ٰ��ص� 
	//���� ������ ���̰� 1�� ������� ��쿡�� nomalize�ؼ� �ھ������.
	//���� ��ī�̹ڽ� VIBuffer�� ���� ���鲨�� ��� �ܼ� �̹��� �ؽ��� ������ ����� UV������.

	//�����(��[ī�޶�] ����) �»��
	pVertices[0].vPos = Vector3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vUV = Vector2(0.f, 0.f);

	//������� �� ���
	pVertices[1].vPos = Vector3(0.5f, 0.5f,-0.5f);
	pVertices[1].vUV = Vector2(1.f, 0.f);

	//������� �� �ϴ�
	pVertices[2].vPos = Vector3(0.5f, -0.5f,-0.5f);
	pVertices[2].vUV = Vector2(1.f, 1.f);

	//������� �� �ϴ�
	pVertices[3].vPos = Vector3(-0.5f,-0.5f,-0.5f);
	pVertices[3].vUV = Vector2(0.f, 1.f);

	//���� �� ���
	pVertices[4].vPos = Vector3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vUV = Vector2(1.f, 0.f);

	//���� �� ���
	pVertices[5].vPos = Vector3(0.5f, 0.5f, 0.5f);
	pVertices[5].vUV = Vector2(0.f, 0.f);

	//���� �� �ϴ�
	pVertices[6].vPos = Vector3(0.5f,-0.5f, 0.5f);
	pVertices[6].vUV = Vector2(0.f, 1.f);

	//���� �� �ϴ�
	pVertices[7].vPos = Vector3(-0.5f,-0.5f, 0.5f);
	pVertices[7].vUV = Vector2(1.f, 1.f);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT Cube_VIBuffer_Texture::Create_IBuffer()
{

	if (FAILED(m_pDX9Device->CreateIndexBuffer(
		m_tVBInfo.m_iPolyCount*m_tIBInfo.m_iIndexMemSize, /* �ε��� �迭�� �� �޸� ������ */
		0,
		m_tIBInfo.m_tIndexFMT, /* � �������� */
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr
	)))
	{
		return E_FAIL;
	}

	INDEX_32* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);
	//�� �迭�� �� �ﰢ���̶�� �����ϸ� ��.

	// +x (������)
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 5;
	pIndices[0]._3 = 6;

	pIndices[1]._1 = 1;
	pIndices[1]._2 = 6;
	pIndices[1]._3 = 2;

	// -x (������)
	pIndices[2]._1 = 4;
	pIndices[2]._2 = 0;
	pIndices[2]._3 = 3;

	pIndices[3]._1 = 4;
	pIndices[3]._2 = 3;
	pIndices[3]._3 = 7;

	// +y (����)
	pIndices[4]._1 = 4;
	pIndices[4]._2 = 5;
	pIndices[4]._3 = 1;

	pIndices[5]._1 = 4;
	pIndices[5]._2 = 1;
	pIndices[5]._3 = 0;

	// -y (�Ʒ���)
	pIndices[6]._1 = 6;
	pIndices[6]._2 = 7;
	pIndices[6]._3 = 3;

	pIndices[7]._1 = 6;
	pIndices[7]._2 = 3;
	pIndices[7]._3 = 2;

	// +z (���� ��)
	pIndices[8]._1 = 5;
	pIndices[8]._2 = 4;
	pIndices[8]._3 = 7;

	pIndices[9]._1 = 5;
	pIndices[9]._2 = 7;
	pIndices[9]._3 = 6;

	// -z (����� ��)
	pIndices[10]._1 = 0;
	pIndices[10]._2 = 1;
	pIndices[10]._3 = 2;

	pIndices[11]._1 = 0;
	pIndices[11]._2 = 2;
	pIndices[11]._3 = 3;

	m_pIB->Unlock();

	return S_OK;

}
