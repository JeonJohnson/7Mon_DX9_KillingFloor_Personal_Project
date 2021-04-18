#include "..\Header\Mesh_Renderer.h"

#include "StaticMesh.h"
#include "AnimMesh.h"
#include "GameObject.h"
#include "ResourceManager.h"

Mesh_Renderer::Mesh_Renderer(Desc * _desc)
{

	//m_pStaticMesh = ResourceManager::Get_Instance()->Get_Resource<StaticMesh>(_desc->szMeshName);

	m_pAnimMesh = ResourceManager::Get_Instance()->Get_Resource<AnimMesh>(_desc->szMeshName);
	assert(L"AnimMesh Loading Failed" && m_pAnimMesh);

	m_pAnimMesh->Set_AnimationSet(_desc->iAnimIndex);

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

	//for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
	//{
	//	m_pStaticMesh->Render_Texture(i);

	//	m_pStaticMesh->Get_Mesh()->DrawSubset(i);
	//}

	for (auto& iter : m_pAnimMesh->Get_MeshContainerList())
	{
		D3DXMESHCONTAINER_DERIVED*		pMeshContainer = iter;

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
			m_pDX9_Device->SetTexture(0, pMeshContainer->ppTexture[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();
		pMeshContainer->pOriginMesh->UnlockVertexBuffer();

	}
}

void Mesh_Renderer::Release()
{
}

AnimMesh * Mesh_Renderer::Get_AnimMesh()
{
	return m_pAnimMesh;
}
