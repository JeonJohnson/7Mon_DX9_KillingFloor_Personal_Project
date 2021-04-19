#include "..\Header\Hierachy_Loader.h"
#include "DeviceManager.h"


Hierachy_Loader::Hierachy_Loader(Desc * _desc)
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	m_szFolderPath = _desc->szPath;
	
	size_t temp = m_szFolderPath.rfind(L"/");
	m_szFolderPath.erase(temp+1);
}

Hierachy_Loader::~Hierachy_Loader()
{
}

HRESULT Hierachy_Loader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	//�� ����� ���� ���M���M
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

	return S_OK;
}

HRESULT Hierachy_Loader::CreateMeshContainer(LPCSTR Name, 
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
	memcpy(pDerivedMeshContainer->pAdjacency,
		pAdjacency, sizeof(DWORD)*dwPolyCount * 3);

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

		pDerivedMeshContainer->ppTexture = new LPDIRECT3DTEXTURE9[pDerivedMeshContainer->NumMaterials];
		ZeroMemory(pDerivedMeshContainer->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pDerivedMeshContainer->NumMaterials);

		memcpy(pDerivedMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pDerivedMeshContainer->NumMaterials);

		//XFile���ο� �ִ� �ؽ��� ���Ϸ�ٰ� �θ����� �̰ž�
		for (DWORD i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
		{
			//wstring szFullTexturePath = L"../../Resource/Test/DynamicMesh/Reference/";
			wstring szFullTexturePath = L"../../Resource/Test/DynamicMesh/";
			//LPSTR
			LPSTR temp = pDerivedMeshContainer->pMaterials[i].pTextureFilename;
			string tempDest = temp;

			wstring szTemp;
			szFullTexturePath += szTemp.assign(tempDest.begin(), tempDest.end());
			//���⼭ ���� �̸��� �Ѱ��� ����.


 			if (FAILED(D3DXCreateTextureFromFile(m_pDX9_Device, szFullTexturePath.c_str(), &pDerivedMeshContainer->ppTexture[i])))
			{		
				return E_FAIL;	
			}
		}

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

	return S_OK;
}

HRESULT Hierachy_Loader::DestroyFrame(LPD3DXFRAME pFrameToFree)
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

HRESULT Hierachy_Loader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	D3DXMESHCONTAINER_DERIVED*	pDerivedMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerToFree;

	for (DWORD i = 0; i < pDerivedMeshContainer->NumMaterials; ++i)
	{
		Safe_Release(pDerivedMeshContainer->ppTexture[i]);	
	}

	Safe_Delete_Arr(pDerivedMeshContainer->ppTexture);

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
