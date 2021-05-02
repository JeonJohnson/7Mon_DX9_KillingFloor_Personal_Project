#include "..\Header\Hierarchy_Loader.h"
#include "DeviceManager.h"
#include "ResourceManager.h"
#include "Texture.h"


Hierarchy_Loader::Hierarchy_Loader(Desc * _desc)
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	m_szMiddleFolderPath = _desc->szMiddlePath;
	
	//���ϸ� �����ֱ�
	size_t temp = m_szMiddleFolderPath.rfind(L"/");
	m_szMiddleFolderPath.erase(temp+1);

	//../../Resource�����ֱ� 
	m_szMiddleFolderPath = ResourceManager::Get_Instance()->EraseFolderPath(m_szMiddleFolderPath);
}

Hierarchy_Loader::~Hierarchy_Loader()
{
}

void Hierarchy_Loader::Release()
{

}

HRESULT Hierarchy_Loader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{//�� ����� ���� ���M���M

	//if (ppNewFrame == nullptr) //zzzzzzzz �ƿ�ǲ��Null�̶�� �����ϴ� �øӻ����� �����ֽ����.
	//{//Static Mesh
	//	//D3DXFrame_Derived*	pDerivedBone = new D3DXFrame_Derived;
	//	//ZeroMemory(pDerivedBone, sizeof(D3DXFrame_Derived));
	//	//*ppNewFrame = pDerivedBone;
	//	return S_OK;
	//}
	//else 
	//{	//Dynamic Mesh

	D3DXFrame_Derived*	pDerivedBone = new D3DXFrame_Derived;
	ZeroMemory(pDerivedBone, sizeof(D3DXFrame_Derived));

	//�̸� ����
	if (Name != nullptr)
	{
		pDerivedBone->Name = new char[strlen(Name) + 1];
		strcpy_s(pDerivedBone->Name, strlen(Name) + 1, Name);
	}

	//CombinedTransformMatirx �ʱ�ȭ
	pDerivedBone->CombinedTransformMatrix = *(D3DXMatrixIdentity(&pDerivedBone->TransformationMatrix));

	//outPut Frame �����ֱ�
	*ppNewFrame = pDerivedBone;
	
	//}
	return S_OK;
}

HRESULT Hierarchy_Loader::CreateMeshContainer(LPCSTR Name,
	CONST D3DXMESHDATA * pMeshData, 
	CONST D3DXMATERIAL * pMaterials, 
	CONST D3DXEFFECTINSTANCE * pEffectInstances, 
	DWORD NumMaterials, 
	CONST DWORD * pAdjacency, 
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
//�Ž� �����̳� ����� ����ƽ �Ž� ���鶧 ó�� 
//�ؽ��� ������ ������ ��. => ����ƽ �Ž��� ���ο� �̸� �޾Ƽ� �ؽ��� �ҷ�����

	if (pSkinInfo == nullptr)
	{//Static Mesh
	//�츮�� ������ ��������� �� ���� �ȿ� ��� ����.
		MeshContainer_Derived*	pTempMesh;
		pTempMesh = new MeshContainer_Derived;
		ZeroMemory(pTempMesh, sizeof(MeshContainer_Derived));

		//�̸� ����.
		pTempMesh->Name = new char[strlen(Name) + 1];
		strcpy_s(pTempMesh->Name, strlen(Name) + 1, Name);

		//�Ž� ����
		pTempMesh->MeshData.Type = D3DXMESHTYPE_MESH;
		pTempMesh->MeshData.pMesh = pMeshData->pMesh;
		
		//LPD3DXMESH	pMesh = pMeshData->pMesh;
		
		//adjacency (-> ���ٿ� ���� ���ؽ�����) ����
		DWORD dwPolyCount = pTempMesh->MeshData.pMesh->GetNumFaces();
		pTempMesh->pAdjacency = new DWORD[dwPolyCount * 3];
		memcpy(pTempMesh->pAdjacency, pAdjacency, sizeof(DWORD)* dwPolyCount * 3);

		//FVF ����
		DWORD	dwFVF = pTempMesh->MeshData.pMesh->GetFVF();

		if (dwFVF & D3DFVF_NORMAL)
		{
			pTempMesh->MeshData.pMesh->CloneMeshFVF(
				pTempMesh->MeshData.pMesh->GetOptions(),
				dwFVF,
				m_pDX9_Device,
				&pTempMesh->MeshData.pMesh);

			//pTempMesh->MeshData.pMesh->CloneMeshFVF(
			//	pTempMesh->MeshData.pMesh->GetOptions(),
			//	dwFVF | D3DFVF_NORMAL | D3DFVF_DIFFUSE,
			//	m_pDX9_Device,
			//	&pTempMesh->MeshData.pMesh);
			//// ������ ����� ������ �������� �븻 ���� ����� ��
			//D3DXComputeNormals(
			//	pTempMesh->MeshData.pMesh,
			//	pTempMesh->pAdjacency);
		}
		else
		{//���� FVF���� �븻������ ������ �ڵ�� ���� �־��ֱ�
			pTempMesh->MeshData.pMesh->CloneMeshFVF(
				pTempMesh->MeshData.pMesh->GetOptions(),
				dwFVF | D3DFVF_NORMAL | D3DFVF_DIFFUSE,
				m_pDX9_Device,
				&pTempMesh->MeshData.pMesh);
			// ������ ����� ������ �������� �븻 ���� ����� ��
			D3DXComputeNormals(
				pTempMesh->MeshData.pMesh,
				pTempMesh->pAdjacency);
		}


		//���׸��� ����
		if(NumMaterials != 0)
		{
			pTempMesh->NumMaterials = NumMaterials;

			pTempMesh->pMaterials = new D3DXMATERIAL[pTempMesh->NumMaterials];
			ZeroMemory(pTempMesh->pMaterials, sizeof(D3DXMATERIAL) * pTempMesh->NumMaterials);
			memcpy(pTempMesh->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pTempMesh->NumMaterials);
			//pTempMesh->ppTexture = new LPDIRECT3DTEXTURE9[pTempMesh->NumMaterials];
			//ZeroMemory(pTempMesh->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pTempMesh->NumMaterials);
			
			//XFile���ο� �ִ� �ؽ��� ���Ϸ�ٰ� �θ����� �̰ž�
			Texture* MeshTextures = nullptr;
	
			for (DWORD i = 0; i < pTempMesh->NumMaterials; ++i)
			{
				//wstring szFullTexturePath = L"../../Resource/Test/DynamicMesh/Reference/";
				wstring szTexturePath;
				string strFileName = pTempMesh->pMaterials[i].pTextureFilename;
				wstring szFileName = L"";
				szFileName.assign(strFileName.begin(), strFileName.end());
				szTexturePath += m_szMiddleFolderPath + szFileName;
				//���⼭ ���� �̸��� �Ѱ��� ����.

				//���ҽ��Ŵ������� �ٿ��ִ°Ŵ� ../../Resource/������
				//���⼭ ���ִ°� oooo.X 
				//�׷� �޾ƿò� �߰� ���� �̸��� �޾ƿ��� �ǰʹ�.
				if(MeshTextures == nullptr)
				{
					MeshTextures = ResourceManager::Get_Instance()->Load_Texture(szTexturePath, 
						ResourceManager::Get_Instance()->EraseFileExtension(szFileName) + L"_Texture");
				}
				else
				{
					ResourceManager::Get_Instance()->Add_Texture(MeshTextures, szTexturePath);
				}
			}
			pTempMesh->pTexture = MeshTextures;
		}
		*ppNewMeshContainer = pTempMesh;
	}
	else
	{//Dynamic Mesh
		MeshContainer_Derived* pDerivedMeshContainer;
		pDerivedMeshContainer = new MeshContainer_Derived;

		//�̸� ����.
		pDerivedMeshContainer->Name = new char[strlen(Name) + 1];
		strcpy_s(pDerivedMeshContainer->Name, strlen(Name) + 1, Name);

		//�Ž� ���� .
		pDerivedMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		LPD3DXMESH	pMesh = pMeshData->pMesh;
		//������ ���� ����
		DWORD dwPolyCount = pMesh->GetNumFaces();
		//adjacency (-> ���ٿ� ���� ���ؽ�����) ����
		pDerivedMeshContainer->pAdjacency = new DWORD[dwPolyCount * 3];
		memcpy(pDerivedMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD)*dwPolyCount * 3);

		//FVF ����
		DWORD	dwFVF = pMesh->GetFVF();

		if (dwFVF & D3DFVF_NORMAL)
		{
			pMesh->CloneMeshFVF(pMesh->GetOptions(),
				dwFVF,
				m_pDX9_Device,
				&pDerivedMeshContainer->MeshData.pMesh);
		}
		else
		{//���� FVF���� �븻������ ������ �ڵ�� ���� �־��ֱ�

			pMesh->CloneMeshFVF(pMesh->GetOptions(),
				dwFVF | D3DFVF_NORMAL,
				m_pDX9_Device,
				&pDerivedMeshContainer->MeshData.pMesh);
			// ������ ����� ������ �������� �븻 ���� ����� ��
			D3DXComputeNormals(pDerivedMeshContainer->MeshData.pMesh,
				pDerivedMeshContainer->pAdjacency);
		}

		//���׸��� ����
		if (NumMaterials != 0)
		{
			pDerivedMeshContainer->NumMaterials = NumMaterials;

			pDerivedMeshContainer->pMaterials = new D3DXMATERIAL[pDerivedMeshContainer->NumMaterials];
			ZeroMemory(pDerivedMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

			//pDerivedMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pDerivedMeshContainer->NumMaterials];
			//ZeroMemory(pDerivedMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pDerivedMeshContainer->NumMaterials);

			memcpy(pDerivedMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);
			
			Texture* MeshTextures = nullptr;

			for (DWORD i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
			{
				wstring szTexturePath;
				string strFileName = pDerivedMeshContainer->pMaterials[i].pTextureFilename;
				wstring szFileName = L"";
				szFileName.assign(strFileName.begin(), strFileName.end());
				szTexturePath += m_szMiddleFolderPath + szFileName;

				if (MeshTextures == nullptr)
				{
					MeshTextures = ResourceManager::Get_Instance()->Load_Texture(szTexturePath,
						ResourceManager::Get_Instance()->EraseFileExtension(szFileName) + L"_Texture");
				}
				else
				{
					ResourceManager::Get_Instance()->Add_Texture(MeshTextures, szTexturePath);
				}
			}
			pDerivedMeshContainer->pTexture = MeshTextures;

		}
		else
		{
			//�������Ͽ� ���׸����� �ϳ��� ���� ���
			//�� ���� �⺻������ �������ش�.
			pDerivedMeshContainer->NumMaterials = 1;

			pDerivedMeshContainer->pMaterials = new D3DXMATERIAL[pDerivedMeshContainer->NumMaterials];
			ZeroMemory(pDerivedMeshContainer->pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

			pDerivedMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pDerivedMeshContainer->NumMaterials];
			ZeroMemory(pDerivedMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pDerivedMeshContainer->NumMaterials);

			pDerivedMeshContainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			pDerivedMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			pDerivedMeshContainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			pDerivedMeshContainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			pDerivedMeshContainer->pMaterials[0].MatD3D.Power = 0.f;

			pDerivedMeshContainer->ppTexture[0] = nullptr;
		}


		//skin Info ����
		if (pSkinInfo == nullptr)
		{
			return E_FAIL;
		}
		pDerivedMeshContainer->pSkinInfo = pSkinInfo;
		pDerivedMeshContainer->pSkinInfo->AddRef();

		pDerivedMeshContainer->
			MeshData.pMesh->
			CloneMeshFVF(pDerivedMeshContainer->MeshData.pMesh->GetOptions(),
				dwFVF, m_pDX9_Device, &pDerivedMeshContainer->pOriginMesh);

		//�޽� �����̳ʿ� ������ ��ġ�� �� ����
		pDerivedMeshContainer->iBoneCount = (int)(pDerivedMeshContainer->pSkinInfo->GetNumBones());

		pDerivedMeshContainer->pFrameOffsetMatrix = new Matrix[pDerivedMeshContainer->iBoneCount];
		ZeroMemory(pDerivedMeshContainer->pFrameOffsetMatrix, sizeof(Matrix) * pDerivedMeshContainer->iBoneCount);

		pDerivedMeshContainer->ppCombinedTrasnformMatrix = new Matrix*[pDerivedMeshContainer->iBoneCount];
		ZeroMemory(pDerivedMeshContainer->ppCombinedTrasnformMatrix, sizeof(Matrix*) * pDerivedMeshContainer->iBoneCount);

		pDerivedMeshContainer->pRenderingMatrix = new Matrix[pDerivedMeshContainer->iBoneCount];
		ZeroMemory(pDerivedMeshContainer->pRenderingMatrix, sizeof(Matrix) * pDerivedMeshContainer->iBoneCount);

		for (int i = 0; i < pDerivedMeshContainer->iBoneCount; ++i)
		{
			pDerivedMeshContainer->pFrameOffsetMatrix[i] = *pDerivedMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);
		}

		*ppNewMeshContainer = pDerivedMeshContainer;
	}
	return S_OK;
}

HRESULT Hierarchy_Loader::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	Safe_Delete_Arr(pFrameToFree->Name);

	if (pFrameToFree->pMeshContainer != nullptr)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (pFrameToFree->pFrameSibling != nullptr)
		DestroyFrame(pFrameToFree->pFrameSibling);

	if (pFrameToFree->pFrameFirstChild != nullptr)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	Safe_Delete(pFrameToFree);

	return S_OK;
}

HRESULT Hierarchy_Loader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
 	D3DXMESHCONTAINER_DERIVED*	pDerivedMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerToFree;

	//for (DWORD i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
	//{
	//	Safe_Release(pDerivedMeshContainer->ppTexture[i]);	
	//}

	//Safe_Delete_Arr(pDerivedMeshContainer->ppTexture);

	Safe_Delete_Arr(pDerivedMeshContainer->pMaterials);
	Safe_Delete_Arr(pDerivedMeshContainer->pAdjacency);


	Safe_Release(pDerivedMeshContainer->MeshData.pMesh);
	Safe_Release(pDerivedMeshContainer->pOriginMesh);
	Safe_Release(pDerivedMeshContainer->pSkinInfo);

	Safe_Delete_Arr(pDerivedMeshContainer->Name);
	Safe_Delete_Arr(pDerivedMeshContainer->pFrameOffsetMatrix);
	Safe_Delete_Arr(pDerivedMeshContainer->ppCombinedTrasnformMatrix);
	Safe_Delete_Arr(pDerivedMeshContainer->pRenderingMatrix);

	Safe_Delete(pDerivedMeshContainer);

	return S_OK;
}
