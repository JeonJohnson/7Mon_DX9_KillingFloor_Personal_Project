#include "..\Header\Mesh.h"

#include "Hierarchy_Loader.h"
#include "AnimationController.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Initialize()
{
	D3DXMatrixIdentity(&m_matMeshTransform);
}

void Mesh::Update()
{
	//Play_AnimationSet();

	D3DXMatrixRotationY(&m_matMeshTransform, D3DXToRadian(-90.f));
	Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &m_matMeshTransform);
}

void Mesh::Release()
{
	Safe_Delete(m_pHierarchyLoader);

}

HRESULT Mesh::Insert_Mesh(const wstring & szFullFilePath, const wstring & szMeshName)
{
	Hierarchy_Loader::Desc hierarchy_desc;
	hierarchy_desc.szMiddlePath = szFullFilePath;
	m_pHierarchyLoader = new Hierarchy_Loader(&hierarchy_desc);

	assert(L"HierachyLoader load failed lol" && m_pHierarchyLoader);

	//LPD3DXANIMATIONCONTROLLER	pAnimController = nullptr;

	if (FAILED(
		D3DXLoadMeshHierarchyFromX(szFullFilePath.c_str(),
			D3DXMESH_MANAGED,
			m_pDX9_Device,
			m_pHierarchyLoader,
			NULL,
			&m_pRootFrame,
			&m_pAnimationController)))
	{
		return E_FAIL;
	}

	if (m_pAnimationController != nullptr)
	{//Dynamic Mesh
		//assert(L"AnimController create failed"&& pAnimController);
		//m_pAnimationController = new AnimationController(pAnimController);

		Matrix temp;
		D3DXMatrixIdentity(&temp);
		//D3DXMatrixRotationY(&temp, D3DXToRadian(-90.f));
		Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &temp);

		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)m_pRootFrame);
	}
	else
	{//Static Mesh


		Matrix temp;
		D3DXMatrixIdentity(&temp);
		//D3DXMatrixRotationY(&temp, D3DXToRadian(-90.f));
		Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &temp);

		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)m_pRootFrame);
		return S_OK;
	}

	return S_OK;
}

void Mesh::Setup_MeshContainerForEachBones(D3DXFrame_Derived * pFrame)
{
	if (pFrame == nullptr)
	{
		return;
	}

	if (pFrame->pMeshContainer != nullptr)
	{
		MeshContainer_Derived* pDerivedMeshContainer = nullptr;
		pDerivedMeshContainer = (MeshContainer_Derived*)pFrame->pMeshContainer;

		for (int i = 0; i < pDerivedMeshContainer->iBoneCount; ++i)
		{
			D3DXFrame_Derived* pFindFrame = nullptr;

			pFindFrame = (D3DXFrame_Derived*)D3DXFrameFind(m_pRootFrame,
				pDerivedMeshContainer->pSkinInfo->GetBoneName(i));

			pDerivedMeshContainer->ppCombinedTrasnformMatrix[i]
				= &pFindFrame->CombinedTransformMatrix;
		}

		m_MeshContainerList.push_back(pDerivedMeshContainer);
	}

	if (pFrame->pFrameSibling != nullptr)
	{
		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameSibling));
	}

	if (pFrame->pFrameFirstChild != nullptr)
	{
		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameFirstChild));
	}

}

void Mesh::Update_BoneMatrix(D3DXFrame_Derived * pBone, Matrix * pParentMatrix)
{
	if (pBone == nullptr)
	{
		return;
	}

	pBone->CombinedTransformMatrix = pBone->TransformationMatrix * (*(pParentMatrix));

	if (pBone->pFrameSibling != nullptr)
	{
		Update_BoneMatrix((D3DXFrame_Derived*)pBone->pFrameSibling, pParentMatrix);
	}

	if (pBone->pFrameFirstChild != nullptr)
	{
		Update_BoneMatrix((D3DXFrame_Derived*)pBone->pFrameFirstChild, &(pBone->CombinedTransformMatrix));
	}
}

//void Mesh::Set_AnimationSet(int _AnimIndex)
//{
//	if (m_pAnimationController != nullptr)
//	{
//		m_pAnimationController->Set_AnimationSet(_AnimIndex);
//	}
//}

//void Mesh::Play_AnimationSet()
//{
//	if (m_pAnimationController != nullptr)
//	{
//		m_pAnimationController->Play_AnimationSet();
//
//		Matrix matTemp;
//		D3DXMatrixIdentity(&matTemp);
//		D3DXMatrixRotationY(&matTemp, D3DXToRadian(-90.f));
//		Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &matTemp);
//	}
//}

list<MeshContainer_Derived*> Mesh::Get_MeshContainerList()
{
	return m_MeshContainerList;
}

//AnimationController * Mesh::Get_AnimationController()
//{
//	return m_pAnimationController;
//}

LPD3DXANIMATIONCONTROLLER Mesh::Get_AnimController()
{
	return m_pAnimationController;
}

D3DXFRAME * Mesh::Get_RootFrame()
{
	return m_pRootFrame;
}

MeshContainer_Derived * Mesh::Get_RootFrame_MeshContainer()
{
	return (MeshContainer_Derived*)m_pRootFrame->pMeshContainer;
}

const Matrix & Mesh::Get_MeshTransformMatrix() const
{
	return m_matMeshTransform;
}

void Mesh::Set_MeshTransformMatrix(const Matrix& _mat)
{
	m_matMeshTransform = _mat;
}
