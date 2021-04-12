#include "..\Header\StaticMesh.h"
#include "DeviceManager.h"

#include "Texture.h"
#include "ResourceManager.h"

StaticMesh::StaticMesh()
{
	Initialize();
}


StaticMesh::~StaticMesh()
{
}

void StaticMesh::Initialize()
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();
	assert(L"Device loading failed at static Mesh." && m_pDX9_Device);
}

void StaticMesh::Release()
{
}

HRESULT StaticMesh::Insert_StaticMesh(const wstring & _szMeshPath, const wstring & _szTexPath)
{
	wstring MeshFullPath = L"../../Resource/" + _szMeshPath;
	wstring TextureFullPath = L"../../Resource/" + _szTexPath;

	if (FAILED(D3DXLoadMeshFromX(
		MeshFullPath.c_str(), /* 메쉬 경로 */
		D3DXMESH_MANAGED, /* 메모리 관리 방법 */
		m_pDX9_Device, /* 다렉9 디바이스 */
		&m_pAdjacency, /* 인접 매쉬접근을 위한 정보 */
		&m_pMaterials, /* 머테리얼  */
		nullptr, /*  */
		&m_ulMaterial_Count, /* 머테리얼 개수 */
		&m_pMesh))) /* 메쉬 주소 */
	{
		return E_FAIL;
	}

	m_pTexture = ResourceManager::Get_Instance()->Load_Texture(_szTexPath, L"Test_StaticMesh_Texture");
	assert(L"Texture Load Failed at static mesh" && m_pTexture);

	for (DWORD i = 0; i < m_ulMaterial_Count; ++i)
	{
		D3DXMATERIAL*	pMaterial = (D3DXMATERIAL*)m_pMaterials->GetBufferPointer();

		wstring temp = L"Test_StaticMesh_Texture";
		temp += L"_" + to_wstring(i);

		if (FAILED(ResourceManager::Get_Instance()->Add_Texture(m_pTexture, _szTexPath, temp)))
		{
			return E_FAIL;
		}

	}

	
	return S_OK;
}

HRESULT StaticMesh::Render_Texture(int _iNum)
{
	if (FAILED(m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))))
	{
		return E_FAIL;
	}

	return S_OK;
	
}

Texture * StaticMesh::Get_Texture()
{
	return m_pTexture;
}

const DWORD & StaticMesh::Get_MaterialCount() const
{
	return m_ulMaterial_Count;
}

LPD3DXMESH StaticMesh::Get_Mesh()
{
	return m_pMesh;
}

void StaticMesh::Set_Texture(Texture * _texture)
{
	m_pTexture = _texture;
}

