#pragma once

#ifndef _ANIMATION_MESH_H_
#define _ANIMATION_MESH_H_

#include "Engine_Include.h"

#include "CResource.h"

class AnimMesh :public CResource
{
public:
	AnimMesh();
	virtual ~AnimMesh();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

public:

public:

public:

private:
	D3DXFRAME*		m_pRootFrame; 
	//Frame => DirectX에서 말하는 Bone
	//애니메이션에서 모든 뼈 정보를 형제, 자식 관계로 가지고 있을꺼고
	//그 관계를 쭉 돌면서 모든 뼈들을 순회 할껀데
	//진입점을 모르니 그 진입점 역할을 해줄 친구.
	//typedef struct _D3DXFRAME 
	//{
	//	LPSTR                   Name; //ㄹㅇ 뼈의 이름
	//	D3DXMATRIX              TransformationMatrix; //뼈의 트랜스폼

	//	LPD3DXMESHCONTAINER     pMeshContainer; //매쉬의 집합체? 매쉬라고 보면 됨.

	//	struct _D3DXFRAME       *pFrameSibling; //형제 뼈. 같은 부모를 가지고 있음.
	//	struct _D3DXFRAME       *pFrameFirstChild; //현재 뼈가 부모가 될 자식 뼈.
	//} D3DXFRAME, *LPD3DXFRAME;

								


};


#endif //_ANIMATION_MESH_H_