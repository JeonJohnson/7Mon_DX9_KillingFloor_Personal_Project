//#pragma once
//
//#ifndef _ANIMATION_MESH_H_
//#define _ANIMATION_MESH_H_
//
//#include "Engine_Include.h"
//
//#include "CResource.h"
//
//#include "Hierachy_Loader.h"
//#include "AnimationController.h"
//
//class DLL_STATE AnimMesh :public CResource
//{
//public:
//	AnimMesh();
//	virtual ~AnimMesh();
//
//public:
//	virtual void Initialize() override;
//	virtual void Update() override;
//	//void		 Render();
//	virtual void Release() override;
//
//public: /* Function */
//	HRESULT		Insert_AnimationMesh(
//		const wstring& szFullFilePath, const wstring& szMeshName = L"");
//	
//	void		Update_BoneMatrix(D3DXFrame_Derived* pBone, Matrix* pParentMatrix);
//	void		Setup_MeshContainerForEachBones(D3DXFrame_Derived* pFrame);
//
//	void		Set_AnimationSet(int _animIndex);
//	void		Play_AnimationSet();
//
//public: /* Get */
//	list<MeshContainer_Derived*>	Get_MeshContainerList();
//	AnimationController*			Get_AnimationController();
//	D3DXFRAME*						Get_RootFrameArr();
//	MeshContainer_Derived*			Get_MeshContainer_forStatic();
//	
//
//public: /* Set */
//
//private:
//	D3DXFRAME*							m_pRootFrame = nullptr; 
//	//Frame => DirectX에서 말하는 Bone
//	//애니메이션에서 모든 뼈 정보를 형제, 자식 관계로 가지고 있을꺼고
//	//그 관계를 쭉 돌면서 모든 뼈들을 순회 할껀데
//	//진입점을 모르니 그 진입점 역할을 해줄 친구.
//	//typedef struct _D3DXFRAME 
//	//{
//	//	LPSTR                   Name; //ㄹㅇ 뼈의 이름
//	//	D3DXMATRIX              TransformationMatrix; //뼈의 트랜스폼
//
//	//	LPD3DXMESHCONTAINER     pMeshContainer; //매쉬의 집합체? 매쉬라고 보면 됨.
//
//	//	struct _D3DXFRAME       *pFrameSibling; //형제 뼈. 같은 부모를 가지고 있음.
//	//	struct _D3DXFRAME       *pFrameFirstChild; //현재 뼈가 부모가 될 자식 뼈.
//	//} D3DXFRAME, *LPD3DXFRAME;
//	list<MeshContainer_Derived*>	m_MeshContainerList;
//
//
//
//	Hierachy_Loader*					m_pHierachyLoader = nullptr;
//	//다이나믹 매쉬를 생성 할 떄 필수적으로 필요한 콜백함수들을 
//	//우리 입맛에 맞게 사용하기위해 Dx에서 제공하는 클래스를 상속받아 만든 클래스.
//
//	AnimationController*				m_pAnimationController = nullptr;
//
//								
//
//
//};
//
//
//#endif //_ANIMATION_MESH_H_