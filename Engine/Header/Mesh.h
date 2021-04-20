#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class Hierachy_Loader;
class AnimationController;

class DLL_STATE  Mesh : public CResource
{
//나중에 둘다 띄어보고
	//스태틱매쉬랑, 애니메이션 매쉬 합칠 클래스.

public:
	Mesh();
	virtual ~Mesh();

public:
	virtual void Initialize() override;
	virtual void Update();
	virtual void Release() override;

public:
	HRESULT		Insert_AnimationMesh(const wstring& szFullFilePath, const wstring& szMeshName = L"");
	
public:

public:

public:

private:
	list<MeshContainer_Derived*>		m_MeshContainerList;

	D3DXFRAME*							m_pRootFrame = nullptr;
	Hierachy_Loader*					m_pHierachyLoader = nullptr;
	AnimationController*				m_pAnimationController = nullptr;

};

#endif //_MESH_H_