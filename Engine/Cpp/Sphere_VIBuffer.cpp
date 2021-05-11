#include "..\Header\Sphere_VIBuffer.h"



Sphere_VIBuffer::Sphere_VIBuffer()
{
	Initialize();
}


Sphere_VIBuffer::~Sphere_VIBuffer()
{
}

void Sphere_VIBuffer::Initialize()
{
	m_iHeightSliceCount = 10;
	m_iWidthSliceCount = 10;
	m_fRadius = 0.5f;


	m_eKind = VIBUFFER_KIND::VIBuffer_Color;

	Set_Name(L"Sphere_Debug");

	VBUFFER_INFO vTemp;
	ZeroMemory(&vTemp, sizeof(VBUFFER_INFO));
	vTemp.m_iVertexCount = (m_iHeightSliceCount - 1) * (m_iWidthSliceCount + 1) + 2;
	vTemp.m_iPolyCount =  m_iWidthSliceCount * 3 
		+ (m_iHeightSliceCount - 2) * (m_iWidthSliceCount) * 6 
		+ m_iWidthSliceCount * 3;
	vTemp.m_iVertexMemSize = sizeof(VERTEX_COLOR);
	vTemp.m_iFVF = FVF_COLOR;
	Set_VBufferInfo(vTemp);

	Create_VBuffer();


	//////////////////////////////////////////
	IBUFFER_INFO iTemp;
	ZeroMemory(&vTemp, sizeof(IBUFFER_INFO));
	iTemp.m_iIndexMemSize = sizeof(INDEX_32);
	iTemp.m_tIndexFMT = D3DFMT_INDEX32;
	Set_IBufferInfo(iTemp);

	Create_IBuffer();
}

HRESULT Sphere_VIBuffer::Create_VBuffer()
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

	VERTEX_COLOR* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	int vertexCount = 0;
	float radius = m_fRadius;
	pVertices[vertexCount].vPos = Vector3(0, radius, 0);
	pVertices[vertexCount].uiColor = D3DCOLOR_RGBA(0, 255, 0, 255);
	

	float phiStep = 3.14159265f / m_iHeightSliceCount;
	float thetaStep = 2.0f * 3.14159265f / m_iWidthSliceCount;

	for (int i = 1; i <= m_iHeightSliceCount - 1; ++i)
	{
		float phi = i * phiStep;

		for (int j = 0; j <= m_iWidthSliceCount; ++j)
		{
			++vertexCount;

			float theta = j * thetaStep;

			pVertices[vertexCount].vPos = Vector3(radius * sinf(phi)* cosf(theta), 
													radius * cosf(phi), 
													radius * sinf(phi)*sinf(theta));

			pVertices[vertexCount].uiColor = D3DCOLOR_RGBA(0, 255, 0, 255);
		}
	}
	++vertexCount;

	pVertices[vertexCount].vPos = Vector3(0, -radius, 0);
	pVertices[vertexCount].uiColor = D3DCOLOR_RGBA(0, 255, 0, 255);

	m_tVBInfo.m_iVertexCount = vertexCount + 1;

	//D3DXComputeBoundingSphere(&vertices[0].position, vertexCount, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT Sphere_VIBuffer::Create_IBuffer()
{
	int totalCount = m_iWidthSliceCount * 3 
		+ (m_iHeightSliceCount - 2) * (m_iWidthSliceCount) * 6 
		+ m_iWidthSliceCount * 3;

	m_pDX9_Device->CreateIndexBuffer(
		sizeof(DWORD) * totalCount,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_pIB,
		nullptr);

	DWORD* indices = nullptr;

	m_pIB->Lock(0, 0, (void**)&indices, 0);

	int count = -1;
	for (int i = 1; i <= m_iWidthSliceCount; ++i)
	{
		++count;
		indices[count] = 0;
		++count;
		indices[count] = i + 1;
		++count;
		indices[count] = i;
	}

	int baseIndex = 1;
	int ringVertexCount = m_iWidthSliceCount + 1;
	for (int i = 0; i < m_iHeightSliceCount - 2; ++i)
	{
		for (int j = 0; j < m_iWidthSliceCount; ++j)
		{
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j;
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j + 1;
			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j;

			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j;
			++count;
			indices[count] = baseIndex + i * ringVertexCount + j + 1;
			++count;
			indices[count] = baseIndex + (i + 1) * ringVertexCount + j + 1;
		}
	}

	int southPoleIndex = (m_iHeightSliceCount - 1) * (m_iWidthSliceCount + 1) + 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < m_iWidthSliceCount; ++i)
	{
		++count;
		indices[count] = southPoleIndex;
		++count;
		indices[count] = baseIndex + i;
		++count;
		indices[count] = baseIndex + i + 1;
	}
	
	m_tVBInfo.m_iPolyCount = ((count + 1) / 3);
	m_pIB->Unlock();

	return S_OK;
}
