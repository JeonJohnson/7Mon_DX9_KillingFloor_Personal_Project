#include "..\Header\Mesh_Renderer.h"

#include "StaticMesh.h"
#include "AnimMesh.h"
#include "Mesh.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"

Mesh_Renderer::Mesh_Renderer(Desc * _desc)
{

	//m_pStaticMesh = ResourceManager::Get_Instance()->Get_Resource<StaticMesh>(_desc->szMeshName);

	m_pAnimMesh = ResourceManager::Get_Instance()->Get_Resource<AnimMesh>(_desc->szMeshName);
	assert(L"AnimMesh Loading Failed" && m_pAnimMesh);

	if (m_pAnimMesh->Get_AnimationController() != nullptr)
	{
		m_pAnimMesh->Set_AnimationSet(_desc->iAnimIndex);
	}

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


	if (m_pAnimMesh->Get_AnimationController() == nullptr)
	{//StaticMesh Rendering

	 //D3DXFRAME���� �޽������̳� �ȿ� �Ž������� ����.

		//for (int i = 0; i < (int)m_pStaticMesh->Get_MaterialCount(); ++i)
		//{
		//	m_pStaticMesh->Render_Texture(i);
					//=> m_pDX9_Device->SetTexture(0, m_pTexture->Get_Texture(_iNum))
		//	m_pStaticMesh->Get_Mesh()->DrawSubset(i);
		//}
		MeshContainer_Derived* temp = m_pAnimMesh->Get_MeshContainer_forStatic();

		Texture* tempTexture = temp->pTexture;

		for (int i = 0; i < (int)m_pAnimMesh->Get_RootFrameArr()->pMeshContainer->NumMaterials; ++i)
		{

			//�� pMesh ������ ���ұ� �� �û�����...?
			void*		pSrcVtx = nullptr;
			void*		pDestVtx = nullptr;

			temp->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

			if (FAILED(m_pDX9_Device->SetTexture(0, tempTexture->Get_Texture(i))))
			{
				assert(0 && L"SetTexture Faild at Static Mesh Renderring");
			}
			if (FAILED(temp->MeshData.pMesh->DrawSubset(i)))
			{
				assert(0 && L"DrawSubSet Failed at Static Mesh Renderring");
			}

			temp->MeshData.pMesh->UnlockVertexBuffer();

		}
	}
	else
	{
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
			// ����Ʈ ���� ��Ű���� �����ϴ� �Լ�
			//(��Ű�� �� �ƴ϶� �ִϸ��̼� ���� ��, ����� ���� �������� ���� ���� ���ÿ� ������ ��)
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

}

void Mesh_Renderer::Release()
{
}

AnimMesh * Mesh_Renderer::Get_AnimMesh()
{
	return m_pAnimMesh;
}
