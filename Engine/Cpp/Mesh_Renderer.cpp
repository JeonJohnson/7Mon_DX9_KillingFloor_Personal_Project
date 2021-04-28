#include "..\Header\Mesh_Renderer.h"

#include "StaticMesh.h"
#include "AnimMesh.h"
#include "Mesh.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"

Mesh_Renderer::Mesh_Renderer(Desc * _desc)
{
	m_pMesh = ResourceManager::Get_Instance()->Get_Resource<Mesh>(_desc->szMeshName);
	assert(L"AnimMesh Loading Failed" && m_pMesh);

	//if (m_pMesh->Get_AnimationController() != nullptr)
	//{
	//	m_pMesh->Set_AnimationSet(_desc->iAnimIndex);
	//}



}

Mesh_Renderer::~Mesh_Renderer()
{
}

void Mesh_Renderer::Initialize()
{
}

void Mesh_Renderer::Update()
{
}

void Mesh_Renderer::LateUpdate()
{
}

void Mesh_Renderer::Render()
{
	m_pDX9_Device->SetTransform(D3DTS_WORLD, &m_GameObject->Get_Transform()->Get_WorldMatrix());


	if (m_pMesh->Get_AnimController() == nullptr)
	{//StaticMesh Rendering

	 //D3DXFRAME안의 메시컨테이너 안에 매쉬정보들 있음.
		//for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
		//{
		//	m_pStaticMesh->Render_Texture(i);
					//=> m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))
		//	m_pStaticMesh->Get_Mesh()->DrawSubset(i);
		//}
		//MeshContainer_Derived* temp = m_pMesh->Get_RootFrame_MeshContainer();
		//	 
		//assert(L"MeshContainer_Derived is nullptr" && temp);

		//Texture* tempTexture = temp->pTexture;

		//for (int i = 0; i < (int)m_pMesh->Get_RootFrame()->pMeshContainer->NumMaterials; ++i)
		//{
		//	//왜 pMesh 접근을 못할까 이 씹새끼는...?
		//	//왜 되지?
		//	if (FAILED(m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i))))
		//	{
		//		assert(0 && L"SetTexture Faild at Static Mesh Renderring");
		//	}
		//	if (FAILED(temp->MeshData.pMesh->DrawSubset(i)))
		//	{
		//		assert(0 && L"DrawSubSet Failed at Static Mesh Renderring");
		//	}
		//}

		for (auto& iter : m_pMesh->Get_MeshContainerList())
		{
			D3DXMESHCONTAINER_DERIVED* pMeshContainer = iter;
			Texture*	tempTexture = pMeshContainer->pTexture;

			for (int i = 0; i < (int)pMeshContainer->NumMaterials; ++i)
			{
				if (FAILED(m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i))))
				{
					assert(0 && L"SetTexture Faild at Static Mesh Renderring");
				}
				if (FAILED(iter->MeshData.pMesh->DrawSubset(i)))
				{
					assert(0 && L"DrawSubSet Failed at Static Mesh Renderring");
				}
			}
		}
	}
	else
	{
		for (auto& iter : m_pMesh->Get_MeshContainerList())
		{
			D3DXMESHCONTAINER_DERIVED*		pMeshContainer = iter;
			Texture* tempTexture = pMeshContainer->pTexture;

			for (int i = 0; i < pMeshContainer->iBoneCount; ++i)
			{
				pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppCombinedTrasnformMatrix[i]);
			}
			void*		pSrcVtx = nullptr;
			void*		pDestVtx = nullptr;
			pMeshContainer->pOriginMesh->LockVertexBuffer(0, &pSrcVtx);
			pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);
			// 소프트 웨어 스키닝을 수행하는 함수
			//(스키닝 뿐 아니라 애니메이션 변경 시, 뼈들과 정점 정보들의 변경 또한 동시에 수행해 줌)
			pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderingMatrix, NULL, pSrcVtx, pDestVtx);
			
			for (DWORD i = 0; i < pMeshContainer->NumMaterials; ++i)
			{
				m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i));
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
			pMeshContainer->pOriginMesh->UnlockVertexBuffer();
		}
	}

}

void Mesh_Renderer::Release()
{

}

Mesh * Mesh_Renderer::Get_Mesh()
{
	return m_pMesh;
}
