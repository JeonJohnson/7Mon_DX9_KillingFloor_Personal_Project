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
//	//Frame => DirectX���� ���ϴ� Bone
//	//�ִϸ��̼ǿ��� ��� �� ������ ����, �ڽ� ����� ������ ��������
//	//�� ���踦 �� ���鼭 ��� ������ ��ȸ �Ҳ���
//	//�������� �𸣴� �� ������ ������ ���� ģ��.
//	//typedef struct _D3DXFRAME 
//	//{
//	//	LPSTR                   Name; //���� ���� �̸�
//	//	D3DXMATRIX              TransformationMatrix; //���� Ʈ������
//
//	//	LPD3DXMESHCONTAINER     pMeshContainer; //�Ž��� ����ü? �Ž���� ���� ��.
//
//	//	struct _D3DXFRAME       *pFrameSibling; //���� ��. ���� �θ� ������ ����.
//	//	struct _D3DXFRAME       *pFrameFirstChild; //���� ���� �θ� �� �ڽ� ��.
//	//} D3DXFRAME, *LPD3DXFRAME;
//	list<MeshContainer_Derived*>	m_MeshContainerList;
//
//
//
//	Hierachy_Loader*					m_pHierachyLoader = nullptr;
//	//���̳��� �Ž��� ���� �� �� �ʼ������� �ʿ��� �ݹ��Լ����� 
//	//�츮 �Ը��� �°� ����ϱ����� Dx���� �����ϴ� Ŭ������ ��ӹ޾� ���� Ŭ����.
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