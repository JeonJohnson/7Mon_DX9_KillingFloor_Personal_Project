//#include "..\Header\AnimMesh.h"
//#include "AnimationController.h"
//
//
//AnimMesh::AnimMesh()
//{
//}
//
//
//AnimMesh::~AnimMesh()
//{
//}
//
//void AnimMesh::Initialize()
//{
//
//}
//
//void AnimMesh::Update()
//{
//	//Play_AnimationSet();
//}
//
//void AnimMesh::Release()
//{
//}
//
//HRESULT AnimMesh::Insert_AnimationMesh(const wstring & szFullFilePath, const wstring & szMeshName)
//{
//	//����ƽ �Ž� �μ�Ʈ ���� �� �� ������µ� �ؽ������� �̸� ���� �� �ʿ� ����...;; 
//	//XFile ���� ����...;;;
//
//	Hierachy_Loader::Desc hierachy_desc;
//	hierachy_desc.szMiddlePath = szFullFilePath;
//	m_pHierachyLoader = new Hierachy_Loader(&hierachy_desc);
//	assert(L"HierachyLoader load failed lol" && m_pHierachyLoader);
//	
//	LPD3DXANIMATIONCONTROLLER	pAnimController = nullptr;
//
//	if (FAILED(
//		D3DXLoadMeshHierarchyFromX(szFullFilePath.c_str(),
//			D3DXMESH_MANAGED,
//			m_pDX9_Device,
//			m_pHierachyLoader,
//			NULL,
//			&m_pRootFrame,
//			&pAnimController)))
//	{
//		//�� �������� HieracyLoader�� �Լ��� ȣ���ؼ�
//		//�⺻ Frame�� Mesh�� ����1�� �ٲ���.
//		return E_FAIL;
//	}
//	
//	if (pAnimController == nullptr)
//	{//static mesh
//		//D3DXFRAME���� �޽������̳� �ȿ� �Ž������� ����.
//
//		//for (int i = 0; i < (int)m_pRootFrame->pMeshContainer->NumMaterials; ++i)
//		//{
//		//	m_pRootFrame->pMeshContainer->pMaterials->
//		//}
//
//		//Setup_MeshContainerForEachBones((D3DXFrame_Derived*)m_pRootFrame);
//	}
//	else 
//	{ // dynamic mesh
//		assert(L"AnimController create failed"&& pAnimController);
//		m_pAnimationController = new AnimationController(pAnimController);
//
//		//m_pAnimationController->Set_AnimContoller(pAnimController);
//
//		//������ CombineMatrix �ʱ�ȭ ���ֱ�.
//		//�ؿ� MeshContainer �ʱ�ȭ�� ���ؼ�.
//		Matrix temp;
//		D3DXMatrixIdentity(&temp);
//		//D3DXMatrixRotationY(&temp, D3DXToRadian(90.f));
//		Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &temp);
//
//		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)m_pRootFrame);
//	}
//
//	return S_OK;
//}
//
//void AnimMesh::Update_BoneMatrix(D3DXFrame_Derived * pFrame, Matrix * pParentMatrix)
//{
//	if (pFrame == nullptr)
//	{
//		return;
//	}
//	//��� ù���������� ������ ���� ������ �� ���� ��� �Լ� ó�� ��������.
//	//D3DXFrame���� �ڽĻ��� �������� ������ �ִµ�
//	//���� �� ���� �� �������� ������ �� ������ �� �������� �ڽĻ� ������
//	//�ٵ� �� ��������?
//	//�ش� ���� Transform����. 
//	//�ִϸ��̼��̶��� �ᱹ �Ž��� �����̴°ǵ�
//	//�Ž� �� ���� ���� �� �ű��� ��123�� �̴ϱ�
//	//���� �����ΰ� Ư�� ������ �ű⿡ �����صδ°���.
//	//������ ���̹޴� ���ؽ�, ���� �޴� ���ؽ�
//	//�׸��� Ű������ ���صΰ�(�ִϸ��̼ǿ����� KeyFrame������ Key)
//	//�ش� Ű������ ���� ��ġ�� ���صΰ� Ű�� Ű�� ���ݻ��̴�
//	//�� ��ġ���� ���� �������ִ°�.
//	//��ư �̷� ������� �� ������ ��� ���� ��������.
//		//=> �̵��� ���� �ִϸ��̼� ��Ʈ���̶� ����.
//
//	//������ �� ���� ������� �ϱ� ������,
//	//�� ���� �����̸� �ٸ� �͵� ���� ����������.
//	//�� ������ ���� ���� �����ΰſ� ���� �����̴°͵� ��123���̴ϱ�
//	//�츮 ũ���̰��� ������ ����Ҷ� �θ� ���ָ� Matrix�θ� ���ġ�� �ٲ�°� ó��
//	//�̰͵� �Ȱ��� �θ� ���� ��Ʈ������ �����ִ°���.
//		//=> ������ �̿��Ѵٸ� ó�� �� �����Ҷ� ����� ��Ʈ������ �ָ�
//			//=> �� �Ž���ü�� �׷��� �����ٴ°�!
//	
//	pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * (*(pParentMatrix));
//
//	if (pFrame->pFrameSibling != nullptr)
//	{
//		Update_BoneMatrix((D3DXFrame_Derived*)pFrame->pFrameSibling, pParentMatrix);
//		//���� ���� �θ� �����ϱ� �״�� �θ� ��Ʈ���� �־��ֱ�
//	}
//
//	if (pFrame->pFrameFirstChild != nullptr)
//	{
//		Update_BoneMatrix((D3DXFrame_Derived*)pFrame->pFrameFirstChild, &(pFrame->CombinedTransformMatrix));
//		//�ڽĻ����״� �� combine��Ʈ������ �θ� ��Ʈ������
//	}
//
//	//=>
//}
//
//void AnimMesh::Setup_MeshContainerForEachBones(D3DXFrame_Derived * pFrame)
//{
//	//Frame, �� ������ Meshcontainer�� ������ ����.
//	//�̰� ���� UpdateBoneMatrix�� �׵���ĵ� �ѹ� �ʱ�ȭ ��Ű��
//	//�̰� ���ͼ� �� ������ ����� �Ž���(�Ž������̳�)�� ������ �ִ°�.
//		//=> �ѹ��� ���ָ� �ȴ� �̰ž� 
//	//�굵 �� ���� ������� ��� ���� ������.
//
//	if (pFrame->pMeshContainer != nullptr)
//	{
//		//���� ���� ������ �ִ� MeshContainer�� �츮�� �����
//		//extension ��������ٰ� ����ȯ�ؼ� ��������.
//		//������ �ּҰ��̶� ����ȯ ���������ϴ�.
//		MeshContainer_Derived* pDerivedMeshContainer = nullptr;
//		pDerivedMeshContainer = (MeshContainer_Derived*)pFrame->pMeshContainer;
//
//		//�� ������ŭ ���ƾ� �ϴϱ� �� ���� �޾ƿͼ� for�� ������
//		for (int i = 0; i < pDerivedMeshContainer->iBoneCount; ++i)
//		{
//			//LPCSTR
//			//const char* lpccBoneName = ;
//			D3DXFrame_Derived* pFindFrame = nullptr;
//			
//			pFindFrame = (D3DXFrame_Derived*)D3DXFrameFind(m_pRootFrame, 
//				pDerivedMeshContainer->pSkinInfo->GetBoneName(i));
//			//��ȣ�� �ش��ϴ� �� �̸��� ��Ʈ������ ���鼭 ã�Ƴ�.
//
//			pDerivedMeshContainer->ppCombinedTrasnformMatrix[i]
//				= &pFindFrame->CombinedTransformMatrix;
//			//�۰� �Ʊ� �� ó�� �Ž��� CombineTransformMatrix�ִµ�
//			//������ �Ѱ��ش�.
//			//�̰� ���߿� ���� �κп��� �����ͼ� RenderMatirx�� ���鲨��
//		}
//
//		m_MeshContainerList.push_back(pDerivedMeshContainer);
//	}
//
//	//�ٸ� ���鵵 ����
//	if(pFrame->pFrameSibling != nullptr)	
//	{
//		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameSibling));
//	}
//
//	if (pFrame->pFrameFirstChild != nullptr)
//	{
//		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameFirstChild));
//	}
//
//
//}
//
//void AnimMesh::Set_AnimationSet(int _animIndex)
//{
//	m_pAnimationController->Set_AnimationSet(_animIndex);
//}
//
//void AnimMesh::Play_AnimationSet()
//{
//	m_pAnimationController->Play_AnimationSet();
//
//	Matrix matTemp;
//	D3DXMatrixIdentity(&matTemp);
//	Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &matTemp);
//}
//
//list<MeshContainer_Derived*> AnimMesh::Get_MeshContainerList()
//{
//	return m_MeshContainerList;
//}
//
//AnimationController * AnimMesh::Get_AnimationController()
//{
//	return m_pAnimationController;
//}
//
//D3DXFRAME * AnimMesh::Get_RootFrameArr()
//{
//	return m_pRootFrame;
//}
//
//MeshContainer_Derived * AnimMesh::Get_MeshContainer_forStatic()
//{
//	return (MeshContainer_Derived*)m_pRootFrame->pMeshContainer;
//}
