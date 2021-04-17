#include "..\Header\AnimMesh.h"
#include "AnimationController.h"


AnimMesh::AnimMesh()
{
}


AnimMesh::~AnimMesh()
{
}

void AnimMesh::Initialize()
{

}

void AnimMesh::Update()
{
	//Update_BoneMatrix();
}

void AnimMesh::Release()
{
}

HRESULT AnimMesh::Insert_AnimationMesh(const wstring & szFullFilePath, const wstring & szMeshName)
{
	//스태틱 매쉬 인설트 지금 잘 못 만들었는디 텍스쳐파일 이름 적어 줄 필요 없음...;; 
	//XFile 내에 있음...;;;

	Hierachy_Loader::Desc hierachy_desc;
	hierachy_desc.szPath = szFullFilePath;
	m_pHierachyLoader = new Hierachy_Loader(&hierachy_desc);
	assert(L"HierachyLoader load failed lol" && m_pHierachyLoader);
	
	LPD3DXANIMATIONCONTROLLER	pAnimContoller = nullptr;

	if (FAILED(
		D3DXLoadMeshHierarchyFromX(szFullFilePath.c_str(),
			D3DXMESH_MANAGED,
			m_pDX9_Device,
			m_pHierachyLoader,
			NULL,
			&m_pRootFrame,
			&pAnimContoller)))
	{
		//이 과정에서 HieracyLoader의 함수를 호출해서
		//기본 Frame과 Mesh을 지정해 줄꺼임.
		return E_FAIL;
	}
	
	


	//뼈들의 CombineMatrix 초기화 해주기.
	//밑에 MeshContainer 초기화를 위해서.
	Matrix temp;
	D3DXMatrixIdentity(&temp);
	Update_BoneMatrix((D3DXFrame_Derived*)m_pRootFrame, &temp);

	Setup_MeshContainerForEachBones((D3DXFrame_Derived*)m_pRootFrame);
	return S_OK;
}

void AnimMesh::Update_BoneMatrix(D3DXFrame_Derived * pFrame, Matrix * pParentMatrix)
{
	//얘는 첫뼈에서부터 마지막 뼈에 도달할 때 까지 재귀 함수 처럼 돌릴꺼임.
	//D3DXFrame보면 자식뼈와 형제뼈를 가지고 있는데
	//형제 뼈 가서 그 형제뼈의 형제뼈 쭉 돌리고 다 돌았으면 자식뼈 돌리고
	//근데 뭘 돌리느냐?
	//해당 뼈의 Transform이지. 
	//애니메이션이란게 결국 매쉬가 움직이는건데
	//매쉬 그 많은 점을 다 옮길라면 지123랄 이니까
	//뼈를 만들어두고 특정 점들을 거기에 연결해두는거임.
	//영향을 많이받는 버텍스, 적게 받는 버텍스
	//그리고 키란것을 정해두고(애니메이션에서의 KeyFrame에서의 Key)
	//해당 키에서의 뼈의 위치를 정해두고 키와 키의 간격사이는
	//그 위치들을 선형 보간해주는것.
	//여튼 이런 방식으로 매 프레임 모든 뼈를 돌릴꺼임.
		//=> 이따가 만들 애니메이션 컨트롤이랑 같이.

	//뼈들은 다 같이 움직어야 하기 때문에,
	//한 뼈가 움직이면 다른 것도 같이 움직여야함.
	//매 프레임 상위 뼈가 움직인거에 따라서 움직이는것도 지123랄이니까
	//우리 크자이공부 순서로 계산할때 부모 해주면 Matrix부모에 상대치로 바뀌는거 처럼
	//이것도 똑같이 부모 뼈의 매트릭스를 곱해주는거임.
		//=> 역으로 이용한다면 처음 딱 진입할때 변경된 매트릭스를 주면
			//=> 이 매쉬자체도 그렇게 먹힌다는것!
	
	pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * (*(pParentMatrix));

	if (pFrame->pFrameSibling != nullptr)
	{
		Update_BoneMatrix((D3DXFrame_Derived*)pFrame->pFrameSibling, pParentMatrix);
		//형제 뼈는 부모가 같으니까 그대로 부모 매트릭스 넣어주기
	}

	if (pFrame->pFrameFirstChild != nullptr)
	{
		Update_BoneMatrix((D3DXFrame_Derived*)pFrame->pFrameFirstChild, &(pFrame->CombinedTransformMatrix));
		//자식뼈한테는 내 combine매트릭스가 부모 매트릭스여
	}

	//=>
}

void AnimMesh::Setup_MeshContainerForEachBones(D3DXFrame_Derived * pFrame)
{
	//Frame, 즉 뼈에서 Meshcontainer을 가지고 있음.
	//이거 전에 UpdateBoneMatrix를 항등행렬도 한번 초기화 시키고
	//이거 들어와서 각 뼈마다 핟당될 매쉬들(매쉬컨테이너)을 지정해 주는거.
		//=> 한번만 해주면 된다 이거야 
	//얘도 뭐 같은 방식으로 모든 뼈를 돌꺼임.

	if (pFrame->pMeshContainer != nullptr)
	{
		//뼈가 원래 가지고 있던 MeshContainer을 우리가 사용할
		//extension 버젼으루다가 형변환해서 가져오기.
		//어차피 주소값이라서 형변환 문제없읍니다.
		MeshContainer_Derived* pDerivedMeshContainer = nullptr;
		pDerivedMeshContainer = (MeshContainer_Derived*)pFrame->pMeshContainer;

		//뼈 개수만큼 돌아야 하니까 뼈 개수 받아와서 for문 돌리기
		for (int i = 0; i < pDerivedMeshContainer->iBoneCount; ++i)
		{
			//LPCSTR
			//const char* lpccBoneName = ;
			D3DXFrame_Derived* pFindFrame = nullptr;
			
			pFindFrame = (D3DXFrame_Derived*)D3DXFrameFind(m_pRootFrame, 
				pDerivedMeshContainer->pSkinInfo->GetBoneName(i));
			//번호에 해당하는 뼈 이름을 루트본부터 돌면서 찾아냄.

			pDerivedMeshContainer->ppCombinedTrasnformMatrix[i]
				= &pFindFrame->CombinedTransformMatrix;
			//글고 아까 뼈 처럼 매쉬도 CombineTransformMatrix있는데
			//값들을 넘겨준다.
			//이건 나중에 렌더 부분에서 가져와서 RenderMatirx를 만들꺼얌
		}

		m_MeshContainerList.push_back(pDerivedMeshContainer);
	}

	//다른 뼈들도 ㄱㄱ
	if(pFrame->pFrameSibling != nullptr)	
	{
		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameSibling));
	}

	if (pFrame->pFrameFirstChild != nullptr)
	{
		Setup_MeshContainerForEachBones((D3DXFrame_Derived*)(pFrame->pFrameFirstChild));
	}


}
