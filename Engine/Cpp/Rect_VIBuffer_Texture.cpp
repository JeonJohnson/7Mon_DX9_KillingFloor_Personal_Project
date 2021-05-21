#include "..\Header\Rect_VIBuffer_Texture.h"


Rect_VIBuffer_Texture::Rect_VIBuffer_Texture()
{
	Initialize();
	//��� �Ŵ������� ���� �ҷ����� ���⼭ �ٷ� �����ų�� �����.
}


Rect_VIBuffer_Texture::~Rect_VIBuffer_Texture()
{
}

void Rect_VIBuffer_Texture::Initialize()
{
	m_eKind = VIBUFFER_KIND::VIBuffer_Textrue;
	m_eDrawType = D3DPT_TRIANGLELIST;

	Set_Name(L"Rect_Texture");

//1. Vertex ���� ����
	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = 4; 
	vTemp.m_iPolyCount = 2;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_TEXTURE);
	vTemp.m_iFVF = FVF_TEXTURE;
	Set_VBufferInfo(vTemp);

	//2. VertexBuffer �����
	if (FAILED(Create_VBuffer()))
	{
		assert(0 && L"Rect_Texture Vertex Buffer Create Failed");
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
		assert(0 && L"Rect_Texture Index Buffer Create Failed");
	}

	//ResourceManager::Get_Instance()->Insert_Resource<VIBuffer,Rect_VIBuffer_Color>()

	///*Test*/
	//TCHAR szTemp[128] = L"../../Resource/Test/boss.png";

	//if (FAILED(D3DXCreateTextureFromFile(m_pDX9_Device, 
	//	szTemp, (LPDIRECT3DTEXTURE9*)&test)))
	//{
	//	assert(L"Texture Create failed" && test);
	//}

}

HRESULT Rect_VIBuffer_Texture::Create_VBuffer()
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
	//�̰� VIBuffer���� ���ִ°� ������ ������... ����; �߸�­��

	VERTEX_TEXTURE* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	//�»�
	pVertices[0].vPos = Vector3(-1.f, 1.f, 0.f);
	pVertices[0].vUV = Vector2(0.f, 0.f);
	pVertices[0].vNormal = Vector3(0.f, 0.f, 0.f);

	//���
	pVertices[1].vPos = Vector3(1.f, 1.f, 0.f);
	pVertices[1].vUV = Vector2(1.f, 0.f);
	pVertices[1].vNormal = Vector3(0.f, 0.f, 0.f);

	//����
	pVertices[2].vPos = Vector3(1.f, -1.f, 0.f);
	pVertices[2].vUV = Vector2(1.f, 1.f);
	pVertices[2].vNormal = Vector3(0.f, 0.f, 0.f);

	//����
	pVertices[3].vPos = Vector3(-1.f, -1.f, 0.f);
	pVertices[3].vUV = Vector2(0.f, 1.f);
	pVertices[3].vNormal = Vector3(0.f, 0.f, 0.f);

	Vector3 vFirst, vSecond, vNormal;
	//�� ��� �ﰢ�� ��������
	vFirst = pVertices[1].vPos - pVertices[0].vPos;
	vSecond = pVertices[2].vPos - pVertices[0].vPos;
	D3DXVec3Cross(&vNormal, &vFirst, &vSecond);
	pVertices[0].vNormal = vNormal;
	pVertices[1].vNormal = vNormal;
	pVertices[2].vNormal = vNormal;

	//�� �ϴ� �ﰢ�� ��������
	vFirst = pVertices[2].vPos - pVertices[0].vPos;
	vSecond = pVertices[3].vPos - pVertices[0].vPos;
	D3DXVec3Cross(&vNormal, &vFirst, &vSecond);
	pVertices[0].vNormal = vNormal;
	pVertices[2].vNormal = vNormal;
	pVertices[3].vNormal = vNormal;


	m_pVB->Unlock();

	return S_OK;

}

HRESULT Rect_VIBuffer_Texture::Create_IBuffer()
{
	if(FAILED(m_pDX9_Device->CreateIndexBuffer(
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
	
	//������ �� �ﰢ��
	pIndices[0]._1 = 0; //������ �ɶ���?
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;
	
	//���� �� �ﰢ��
	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;
		//�븻���� ����


	m_pIB->Unlock();

	return S_OK;

}

void Rect_VIBuffer_Texture::Set_Texture(Texture * _pTexture)
{
	assert(L"Texture is nullptr" && _pTexture);

	m_pTexture = _pTexture;
}

HRESULT Rect_VIBuffer_Texture::Render_Texture(int _iNum)
{

	if (FAILED(m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT Rect_VIBuffer_Texture::Render_Texture(LPD3DXEFFECT _pEffect, const char* _ShaderTexName, int _iTexNum)
{
	HRESULT	Temp = _pEffect->SetTexture(_ShaderTexName, m_pTexture->Get_Texture(_iTexNum));
	return Temp;
}
