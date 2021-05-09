// NaviMeshTool_Dialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "NaviMeshTool_Dialog.h"
#include "afxdialogex.h"
#include "Mesh_Renderer.h"
#include "NaviPoint.h"
#include "NaviCell.h"
#include "NaviMesh.h"
#include "NaviMeshTestObj_Move.h"


// NaviMeshTool_Dialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(NaviMeshTool_Dialog, CDialogEx)

NaviMeshTool_Dialog::NaviMeshTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NaviMesh_Dialog, pParent)

{
	m_pNaviMesh = new NaviMesh;
}

NaviMeshTool_Dialog::~NaviMeshTool_Dialog()
{
}

void NaviMeshTool_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_PointCreate, m_checkPointCreate);
	DDX_Control(pDX, IDC_LIST_NaviPointList, m_PointList);
}




BEGIN_MESSAGE_MAP(NaviMeshTool_Dialog, CDialogEx)
	ON_BN_CLICKED(IDC_DeleteVertex_BUTTON, &NaviMeshTool_Dialog::OnBnClickedDeletevertexButton)
	
	ON_BN_CLICKED(IDC_CHECK_PointCreate, &NaviMeshTool_Dialog::OnBnClickedCheckPointcreate)
	ON_BN_CLICKED(IDC_BUTTON2, &NaviMeshTool_Dialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// NaviMeshTool_Dialog 메시지 처리기입니다.


void NaviMeshTool_Dialog::OnBnClickedDeletevertexButton()
{
}

void NaviMeshTool_Dialog::Update_Info()
{
	m_vMousePos.x = (FLOAT)g_pDefaultView->m_tMousePos_View.x;
	m_vMousePos.y = (FLOAT)g_pDefaultView->m_tMousePos_View.y;

	if (m_iNaviPointIndex < 3)
	{
		Create_NaviPoint_First();
	}
	else 
	{
		Create_NaviPoint();
	}

	if (m_pPickingPoint[0] == nullptr)
	{
		NaviPoint* Temp = nullptr;
		if (Picking_Ray2Sphere(&Temp))
		{
			m_pPickingPoint[0] = Temp;
		}
	}
	else if(m_pPickingPoint[0] != nullptr
		&& m_pPickingPoint[1] == nullptr)
	{
		NaviPoint* Temp = nullptr;

		if (Picking_Ray2Sphere(&Temp))
		{
			if (m_pPickingPoint[0] == Temp)
			{
				Notice(L"plz select another Sphere");
			}
			else 
			{
				m_pPickingPoint[1] = Temp;
			}
		}
	}

	
}

//void NaviMeshTool_Dialog::Create_NaviPoint(const Vector3 & _WorldPos, GameObject* _PickingPoint)
//{
//	UpdateData(TRUE);
//
//	if (m_iNaviPointIndex < 3)
//	{ //처음 3개 찍을때
//		if (m_pTempCell == nullptr)
//		{
//			m_pTempCell = new NaviCell;
//		}
//
//		m_pTempPoint = Create_Sphere(_WorldPos);
//		
//		if (m_pTempCell->Get_PointArraySize() < 3)
//		{
//			m_pTempCell->Insert_NaviPoint(m_pTempPoint, m_iNaviPointIndex % 3);
//			m_pTempCell->Setup_Lines();
//
//			if (m_pTempCell->Get_PointArraySize() >= 3)
//			{
//				m_pNaviMesh->Insert_NaviCell(m_pTempCell);
//				m_pTempCell = nullptr;
//			}
//			m_pTempPoint = nullptr;
//		}		
//	}
//	else 
//	{ //그외에 이제 2개 선택해서 찍어야 할 때.
//		if (m_pTempCell == nullptr)
//		{
//			m_pTempCell = new NaviCell;
//		}
//		
//		if (m_pTempCell != nullptr)
//		{
//			if (m_pTempCell->Get_PointArraySize() == 0
//				|| m_pTempCell->Get_PointArraySize() == 1)
//			{
//				if (m_pTempPoint == nullptr)
//				{
//					if (_PickingPoint != nullptr)
//					{
//						m_pTempPoint = _PickingPoint->Get_Component<NaviPoint>();
//						if (m_pTempCell->Get_PointArraySize() == 0)
//						{
//							m_pTempCell->Insert_NaviPoint(m_pTempPoint, 0);
//						}
//						if (m_pTempCell->Get_PointArraySize() == 1)
//						{
//							m_pTempCell->Insert_NaviPoint(m_pTempPoint, 1);
//						}
//
//						m_pTempPoint = nullptr;
//					}
//
//				}
//			}
//			else if (m_pTempCell->Get_PointArraySize() == 2)
//			{
//				if (m_pTempPoint == nullptr)
//				{
//					if(_PickingPoint != nullptr)
//					{
//						m_pTempPoint = Create_Sphere(_WorldPos);
//						m_pTempCell->Insert_NaviPoint(m_pTempPoint, m_iNaviPointIndex % 3);
//						m_pTempCell->Setup_Lines();
//
//						if (m_pTempCell->Get_PointArraySize() >= 3)
//						{
//							m_pNaviMesh->Insert_NaviCell(m_pTempCell);
//							m_pTempCell = nullptr;
//						}
//						m_pTempPoint = nullptr;
//
//					}
//				}
//			}
//			
//
//		}
//
//
//
//	}
//
//
//
//	m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());
//	
//	++m_iNaviPointIndex;
//
//	UpdateData(FALSE);
//}

void NaviMeshTool_Dialog::Create_Ray()
{
	m_vRayOrigin = {0.f,0.f,0.f};

	EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, 0, &m_vRayDir);
	//거리 0이라서 결국 걍 카메라 위치/RayOrigin이랑 같음.

	/* 월드스페이스 변환 */
	Matrix invViewSpace;
	EngineFunction->Get_Dx9_Device()->GetTransform(D3DTS_VIEW, &invViewSpace);
	D3DXMatrixInverse(&invViewSpace, 0, &invViewSpace);
	//시작 지점은 위치 벡터(w = 1)
	//=>TransformCoord
	D3DXVec3TransformCoord(&m_vRayOrigin, &m_vRayOrigin, &invViewSpace);

	//방향은 방향벡터(w = 0)
	//=>TransformNormal
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &invViewSpace);
	//노말라이즈까지.
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);

}

NaviPoint* NaviMeshTool_Dialog::Create_Sphere(const Vector3 & _WorldPos, int _Index)
{
	GameObject* pNaviPoint = INSTANTIATE(OBJECT_TAG_NAVIPOINT, L"NaviPoint_" + to_wstring(m_iNaviPointIndex));
	pNaviPoint->Set_Position(_WorldPos);

	Mesh_Renderer::Desc Render_Desc;
	Render_Desc.szMeshName = L"DebugSphere";
	pNaviPoint->Add_Component<Mesh_Renderer>(&Render_Desc);

	NaviPoint::Desc NaviPoint_Desc;
	NaviPoint_Desc.Pos = _WorldPos;
	NaviPoint_Desc.Index = _Index;
	pNaviPoint->Add_Component<NaviPoint>(&NaviPoint_Desc);

	NaviPoint* temp = pNaviPoint->Get_NewComponent<NaviPoint>();
	return temp;
}

void NaviMeshTool_Dialog::Create_NaviPoint_First()
{
	if (MouseDown(KEY_STATE_LMouse) && KeyPress(KEY_STATE_LCtrl) && m_bPointCreate)
	{
		Vector3 vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, 100);

		vWorldPos.y = 0;

		if (m_pTempCell == nullptr)
		{
			m_pTempCell = new NaviCell;
		}

		m_pTempPoint = Create_Sphere(vWorldPos, m_iNaviPointIndex);
		assert(L"Point is nullptr" && m_pTempPoint);

		if (m_pTempCell->Get_PointArraySize() < 3)
		{
			m_pTempCell->Insert_NaviPoint(m_pTempPoint, m_iNaviPointIndex % 3);
			m_pTempCell->Setup_Lines();
			

			if (m_pTempCell->Get_PointArraySize() >= 3)
			{
				m_pTempCell->Set_CellIndex(m_iCellIndex);
				++m_iCellIndex;
				m_pNaviMesh->Insert_NaviCell(m_pTempCell);

				m_pTempCell = nullptr;
					
			}
			m_pTempPoint = nullptr;
		}

		m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());

		++m_iNaviPointIndex;
		
	}

}

bool NaviMeshTool_Dialog::Picking_Ray2Sphere(NaviPoint** _pOutNaviPoint)
{
	

	if (MouseDown(KEY_STATE_LMouse) && KeyPress(KEY_STATE_LAlt) && m_bPointCreate)
	{
		

		auto naviPoints = EngineFunction->Get_GameObjectListbyTag(OBJECT_TAG_NAVIPOINT);

		if(naviPoints.size() == 0)
		{
			Notice(L"There's no Sphere");
			return false;
		}

		Create_Ray();

		vector<GameObject*>		vecPickObj;
		vector<float>			vecDistance;
		vector<Vector3>			vecIntersection;

		for (auto& naviPoint : naviPoints)
		{
			Vector3		vSphereCenter = naviPoint->Get_Position();
			float		fSphereRadius = 2.f;

			Vector3 l = vSphereCenter - m_vRayOrigin;

			//float fLength_L = D3DXVec3Length(&l);
			//D3DXVec3Normalize(&l, &l);

			double s = D3DXVec3Dot(&l, &m_vRayDir);
			double l2 = D3DXVec3Dot(&l, &l);
			double r2 = pow(fSphereRadius, 2);

			if (s < 0 && l2 > r2)
			{//광선의 구의 반대 방향
				//구를 지나친 경우
				
				continue;
			}

			double m2 = l2 - pow(s, 2);

			if (m2 > r2)
			{//광선이 구를 빗겨가는 경우.
				//return false;
				continue;
			}

			double q = sqrt(r2 - m2);

			float fDistance = 0;
			if (l2 > r2)
			{
				fDistance = (float)(s - q);
			}
			else
			{
				fDistance = (float)(s + q);
			}
			vecDistance.emplace_back(fDistance/* * fLength_L*/);
			vecIntersection.emplace_back(m_vRayOrigin + fDistance*m_vRayDir);
			vecPickObj.emplace_back(naviPoint);
		}

		if (vecPickObj.size() == 0)
		{
			return false;
		}

		if (vecPickObj.size() == 1)
		{
			//*_PickingOjbect = vecPickObj.front();
			//*_fpOutDistance = vecDistance.front();
			//*_vpOutIntersection = vecIntersection.front();

			//return vecPickObj.front();

			int index = vecPickObj.front()->Get_Component<NaviPoint>()->Get_Index();
			wstring szTemp = L"Select " + to_wstring(index) + L"_Point";
			Notice(szTemp.c_str());

			*_pOutNaviPoint = vecPickObj.front()->Get_Component<NaviPoint>();
			return true;
		}

		if (vecPickObj.size() > 1)
		{//거리 계산해야하는디... 다른 칸에 있네...

			float	fShortest;
			int		iCount;

			for (int i = 0; i < vecDistance.size(); ++i)
			{
				if (i == 0)
				{
					fShortest = vecDistance[i];
				}
				else
				{
					if (fShortest < vecDistance[i])
					{
						fShortest = vecDistance[i];
						iCount = i;
					}
				}
			}

			//if (_fpOutDistance != nullptr)
			//{
			//	*_fpOutDistance = fLongest;
			//}
			//if (_vpOutIntersection != nullptr)
			//{
			//	*_vpOutIntersection = vecIntersection[iCount];
			//}

			//*_PickingOjbect = vecPickObj[iCount];
			//return true;
			int index = vecPickObj[iCount]->Get_Component<NaviPoint>()->Get_Index();
			wstring szTemp = L"Select " + to_wstring(index) + L"_Point";
			Notice(szTemp.c_str());

			*_pOutNaviPoint = vecPickObj[iCount]->Get_Component<NaviPoint>();

			return true;
		}


		return false;
	}
	return false;
}

void NaviMeshTool_Dialog::Create_NaviPoint()
{
	if (MouseDown(KEY_STATE_LMouse) && KeyPress(KEY_STATE_LCtrl) && m_bPointCreate)
	{

		Vector3 vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, 100);

		vWorldPos.y = 0;

		int nullCount = 0;
		
		for (int i = 0; i < 2; ++i)
		{
			if (m_pPickingPoint[i] == nullptr)
			{
				++nullCount;
			}
		}

		if (nullCount == 1)
		{
			Notice(L"Plz Select sphere 1 more");
			return;
		}

		if (nullCount == 2)
		{
			Notice(L"Plz Select sphere 2 more");
			return;
		}

		if (nullCount == 0)
		{
			if (m_pTempCell == nullptr)
			{
				m_pTempCell = new NaviCell;
				
				m_pTempCell->Insert_NaviPoint(m_pPickingPoint[0], 0);
				m_pTempCell->Insert_NaviPoint(m_pPickingPoint[1], 1);

				m_pTempPoint = Create_Sphere(vWorldPos,m_iNaviPointIndex);
				m_pTempCell->Insert_NaviPoint(m_pTempPoint, 2);

				m_pTempCell->Setup_Lines();
				m_pTempCell->Set_CellIndex(m_iCellIndex);

				if (m_pTempCell->Get_PointArraySize() >= 3)
				{
					m_pNaviMesh->Insert_NaviCell(m_pTempCell);
					m_pNaviMesh->Link_Cells();
					m_pTempCell = nullptr;
					m_pTempPoint = nullptr;
					m_pPickingPoint[0] = nullptr;
					m_pPickingPoint[1] = nullptr;
				}
				m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());

				++m_iNaviPointIndex;
				++m_iCellIndex;
			}


		}
	}
}




void NaviMeshTool_Dialog::OnBnClickedCheckPointcreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (m_checkPointCreate.GetCheck())
	{//체크 안돼 있을 때.
		m_checkPointCreate.SetCheck(true);
		m_bPointCreate = true;
	}
	else 
	{//체크 돼 있을 때.

		m_checkPointCreate.SetCheck(false);
		m_bPointCreate = false;
	}


	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	GameObject* temp= EngineFunction->Get_GameObjectbyName(L"NaviMesh_Test");

	temp->Get_Component<NaviMeshTestObj_Move>()->Set_NaviMesh(m_pNaviMesh);
}
