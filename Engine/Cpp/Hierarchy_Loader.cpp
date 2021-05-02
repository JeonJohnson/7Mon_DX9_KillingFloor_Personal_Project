#include "..\Header\Hierarchy_Loader.h"
#include "DeviceManager.h"
#include "ResourceManager.h"
#include "Texture.h"


Hierarchy_Loader::Hierarchy_Loader(Desc * _desc)
{
	m_pDX9_Device = DeviceManager::Get_Instance()->Get_DX9_Device();

	m_szMiddleFolderPath = _desc->szMiddlePath;
	
	//파일명 지워주기
	size_t temp = m_szMiddleFolderPath.rfind(L"/");
	m_szMiddleFolderPath.erase(temp+1);

	//../../Resource지워주기 
	m_szMiddleFolderPath = ResourceManager::Get_Instance()->EraseFolderPath(m_szMiddleFolderPath);
}

Hierarchy_Loader::~Hierarchy_Loader()
{
}

void Hierarchy_Loader::Release()
{

}

HRESULT Hierarchy_Loader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{//뼈 만드는 공장 뜎딲뜎딲

	//if (ppNewFrame == nullptr) //zzzzzzzz 아웃풋에Null이라고 리턴하는 플머새끼가 여기있스빈다.
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

	//이름 설정
	if (Name != nullptr)
	{
		pDerivedBone->Name = new char[strlen(Name) + 1];
		strcpy_s(pDerivedBone->Name, strlen(Name) + 1, Name);
	}

	//CombinedTransformMatirx 초기화
	pDerivedBone->CombinedTransformMatrix = *(D3DXMatrixIdentity(&pDerivedBone->TransformationMatrix));

	//outPut Frame 돌려주기
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
//매쉬 컨테이너 만들고 스태틱 매쉬 만들때 처럼 
//텍스쳐 같은거 지정해 줌. => 스태틱 매쉬도 내부에 이름 받아서 텍스쳐 불러오기

	if (pSkinInfo == nullptr)
	{//Static Mesh
	//우리가 일일이 만들었던거 다 여기 안에 들어 있음.
		MeshContainer_Derived*	pTempMesh;
		pTempMesh = new MeshContainer_Derived;
		ZeroMemory(pTempMesh, sizeof(MeshContainer_Derived));

		//이름 세팅.
		pTempMesh->Name = new char[strlen(Name) + 1];
		strcpy_s(pTempMesh->Name, strlen(Name) + 1, Name);

		//매쉬 세팅
		pTempMesh->MeshData.Type = D3DXMESHTYPE_MESH;
		pTempMesh->MeshData.pMesh = pMeshData->pMesh;
		
		//LPD3DXMESH	pMesh = pMeshData->pMesh;
		
		//adjacency (-> 접근용 인접 버텍스공간) 설정
		DWORD dwPolyCount = pTempMesh->MeshData.pMesh->GetNumFaces();
		pTempMesh->pAdjacency = new DWORD[dwPolyCount * 3];
		memcpy(pTempMesh->pAdjacency, pAdjacency, sizeof(DWORD)* dwPolyCount * 3);

		//FVF 설정
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
			//// 인접한 면들의 정보를 기준으로 노말 값을 만들어 줌
			//D3DXComputeNormals(
			//	pTempMesh->MeshData.pMesh,
			//	pTempMesh->pAdjacency);
		}
		else
		{//만약 FVF에서 노말정보가 없으면 코드로 직접 넣어주기
			pTempMesh->MeshData.pMesh->CloneMeshFVF(
				pTempMesh->MeshData.pMesh->GetOptions(),
				dwFVF | D3DFVF_NORMAL | D3DFVF_DIFFUSE,
				m_pDX9_Device,
				&pTempMesh->MeshData.pMesh);
			// 인접한 면들의 정보를 기준으로 노말 값을 만들어 줌
			D3DXComputeNormals(
				pTempMesh->MeshData.pMesh,
				pTempMesh->pAdjacency);
		}


		//머테리얼 세팅
		if(NumMaterials != 0)
		{
			pTempMesh->NumMaterials = NumMaterials;

			pTempMesh->pMaterials = new D3DXMATERIAL[pTempMesh->NumMaterials];
			ZeroMemory(pTempMesh->pMaterials, sizeof(D3DXMATERIAL) * pTempMesh->NumMaterials);
			memcpy(pTempMesh->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * pTempMesh->NumMaterials);
			//pTempMesh->ppTexture = new LPDIRECT3DTEXTURE9[pTempMesh->NumMaterials];
			//ZeroMemory(pTempMesh->ppTexture, sizeof(LPDIRECT3DTEXTURE9) * pTempMesh->NumMaterials);
			
			//XFile내부에 있는 텍스쳐 파일루다가 부를꺼다 이거야
			Texture* MeshTextures = nullptr;
	
			for (DWORD i = 0; i < pTempMesh->NumMaterials; ++i)
			{
				//wstring szFullTexturePath = L"../../Resource/Test/DynamicMesh/Reference/";
				wstring szTexturePath;
				string strFileName = pTempMesh->pMaterials[i].pTextureFilename;
				wstring szFileName = L"";
				szFileName.assign(strFileName.begin(), strFileName.end());
				szTexturePath += m_szMiddleFolderPath + szFileName;
				//여기서 파일 이름만 넘겨줌 지금.

				//리소스매니저에서 붙여주는거는 ../../Resource/까지고
				//여기서 내주는건 oooo.X 
				//그럼 받아올껀 중간 파일 이름만 받아오면 되것다.
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

		//이름 설정.
		pDerivedMeshContainer->Name = new char[strlen(Name) + 1];
		strcpy_s(pDerivedMeshContainer->Name, strlen(Name) + 1, Name);

		//매쉬 설정 .
		pDerivedMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		LPD3DXMESH	pMesh = pMeshData->pMesh;
		//폴리곤 개수 세팅
		DWORD dwPolyCount = pMesh->GetNumFaces();
		//adjacency (-> 접근용 인접 버텍스공간) 설정
		pDerivedMeshContainer->pAdjacency = new DWORD[dwPolyCount * 3];
		memcpy(pDerivedMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD)*dwPolyCount * 3);

		//FVF 설정
		DWORD	dwFVF = pMesh->GetFVF();

		if (dwFVF & D3DFVF_NORMAL)
		{
			pMesh->CloneMeshFVF(pMesh->GetOptions(),
				dwFVF,
				m_pDX9_Device,
				&pDerivedMeshContainer->MeshData.pMesh);
		}
		else
		{//만약 FVF에서 노말정보가 없으면 코드로 직접 넣어주기

			pMesh->CloneMeshFVF(pMesh->GetOptions(),
				dwFVF | D3DFVF_NORMAL,
				m_pDX9_Device,
				&pDerivedMeshContainer->MeshData.pMesh);
			// 인접한 면들의 정보를 기준으로 노말 값을 만들어 줌
			D3DXComputeNormals(pDerivedMeshContainer->MeshData.pMesh,
				pDerivedMeshContainer->pAdjacency);
		}

		//머테리얼 설정
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
			//엑스파일에 머테리얼이 하나도 없을 경우
			//다 직점 기본값으로 세팅해준다.
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


		//skin Info 설정
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

		//메쉬 컨테이너에 영향을 미치는 뼈 설정
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
