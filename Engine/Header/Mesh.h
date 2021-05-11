#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class Hierarchy_Loader;
class AnimationController;

class DLL_STATE  Mesh : public CResource///////////
{
//나중에 둘다 띄어보고
	//스태틱매쉬랑, 애니메이션 매쉬 합칠 클래스.

public:
	explicit Mesh();
	virtual ~Mesh();

public:
	virtual void Initialize() override;
	virtual void Update();
	virtual void Release() override;

public:
	HRESULT		Insert_Mesh(const wstring& szFullFilePath, const wstring& szMeshName = L"");
	
	void		Setup_MeshContainerForEachBones(D3DXFrame_Derived* pFrame);
	void		Update_BoneMatrix(D3DXFrame_Derived* pBone, Matrix* pParentMatrix);

	//void		Set_AnimationSet(int _AnimIndex);
	//void		Play_AnimationSet();


public: /* Get */
	list<MeshContainer_Derived*>		Get_MeshContainerList();
	//AnimationController*				Get_AnimationController();
	LPD3DXANIMATIONCONTROLLER			Get_AnimController();
	D3DXFRAME*							Get_RootFrame();
	MeshContainer_Derived*				Get_RootFrame_MeshContainer();

	const Matrix&						Get_MeshTransformMatrix() const;

public: /* Set */
	void								Set_MeshTransformMatrix(const Matrix& _mat);

private:
	list<MeshContainer_Derived*>		m_MeshContainerList;

	D3DXFRAME*							m_pRootFrame = nullptr;
	Hierarchy_Loader*					m_pHierarchyLoader = nullptr;
	//AnimationController*				m_pAnimationController = nullptr;
	LPD3DXANIMATIONCONTROLLER			m_pAnimationController = nullptr;

	Matrix								m_matMeshTransform;
};

#endif //_MESH_H_