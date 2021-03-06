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
#include "..\..\Engine\Header\SaveInfo_NaviMesh.h"


// NaviMeshTool_Dialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(NaviMeshTool_Dialog, CDialogEx)

NaviMeshTool_Dialog::NaviMeshTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NaviMesh_Dialog, pParent)

	, m_csPointPosX(_T(""))
	, m_csPointPosY(_T(""))
	, m_csPointPosZ(_T(""))
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
	DDX_Text(pDX, IDC_VerPosX_EDIT, m_csPointPosX);
	DDX_Text(pDX, IDC_VerPosY_EDIT, m_csPointPosY);
	DDX_Text(pDX, IDC_VerPosZ_EDIT, m_csPointPosZ);
}




BEGIN_MESSAGE_MAP(NaviMeshTool_Dialog, CDialogEx)
	ON_BN_CLICKED(IDC_DeleteVertex_BUTTON, &NaviMeshTool_Dialog::OnBnClickedDeletevertexButton)
	
	ON_BN_CLICKED(IDC_CHECK_PointCreate, &NaviMeshTool_Dialog::OnBnClickedCheckPointcreate)
	ON_BN_CLICKED(IDC_BUTTON2, &NaviMeshTool_Dialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_NaviMeshSave_Button, &NaviMeshTool_Dialog::OnBnClickedNavimeshsaveButton)
	ON_BN_CLICKED(IDC_NaviMeshLoad_Button, &NaviMeshTool_Dialog::OnBnClickedNavimeshloadButton)
	ON_LBN_SELCHANGE(IDC_LIST_NaviPointList, &NaviMeshTool_Dialog::OnLbnSelchangeListNavipointlist)
	ON_EN_CHANGE(IDC_VerPosX_EDIT, &NaviMeshTool_Dialog::OnEnChangeVerposxEdit)
	ON_EN_CHANGE(IDC_VerPosY_EDIT, &NaviMeshTool_Dialog::OnEnChangeVerposyEdit)
	ON_EN_CHANGE(IDC_VerPosZ_EDIT, &NaviMeshTool_Dialog::OnEnChangeVerposzEdit)
END_MESSAGE_MAP()


// NaviMeshTool_Dialog 메시지 처리기입니다.


void NaviMeshTool_Dialog::OnBnClickedDeletevertexButton()
{
}

void NaviMeshTool_Dialog::Update_Info()
{
	UpdateData(TRUE);

	if (m_pMainCam == nullptr)
	{
		m_pMainCam = EngineFunction->Get_MainCamera();
	}

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
	else if (m_pPickingPoint[1] != nullptr
		&& m_pPickingPoint[2] == nullptr)
	{
		NaviPoint * Temp = nullptr;
		
		if (Picking_Ray2Sphere(&Temp))
		{
			if (m_pPickingPoint[0] == Temp)
			{
				Notice(L"Plz Select Another Sphere");
			}
			else if (m_pPickingPoint[1] == Temp)
			{
				Notice(L"Plz Select Another Sphere");
			}
			else 
			{
				m_pPickingPoint[2] = Temp;
				
				//여기서 하나 Cell 새로 생성하면 될듯.
				if (m_pTempCell == nullptr)
				{
					m_pTempCell = new NaviCell;
					for (int i = 0; i < 3; ++i)
					{
						m_pTempCell->Insert_NaviPoint(m_pPickingPoint[i], i);
					}
					m_pTempCell->Setup_Lines();
					m_pTempCell->Set_CellIndex(m_iCellIndex);

					if (m_pTempCell->Get_PointArraySize() >= 3)
					{
						m_pNaviMesh->Insert_NaviCell(m_pTempCell);
						m_pNaviMesh->Link_Cells();
						m_pTempCell = nullptr;
						m_pTempPoint = nullptr;
						for (int i = 0; i < 3; ++i)
						{
							m_pPickingPoint[i] = nullptr;
						}
					}
					++m_iCellIndex;
					

				}


			}
		}
	}

	if (m_pSelectPoint != nullptr)
	{
		//Vector3 m_vPos = m_mapPoint[m_iCurIndex]->Get_Position();
		m_vPointPostion = m_pSelectPoint->Get_Position();

		m_csPointPosX.Format(L"%.2f", m_vPointPostion.x);
		m_csPointPosY.Format(L"%.2f", m_vPointPostion.y);
		m_csPointPosZ.Format(L"%.2f", m_vPointPostion.z);
	}

	UpdateData(FALSE);
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
		float YTemp = m_pMainCam->Get_Transform()->Get_Position().y;

		Vector3 vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, YTemp);

		//Vector3 vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, 100);

		vWorldPos.y = 0;

		if (m_pTempCell == nullptr)
		{
			m_pTempCell = new NaviCell;
		}

		m_pTempPoint = Create_Sphere(vWorldPos, m_iNaviPointIndex);
		assert(L"Point is nullptr" && m_pTempPoint);
		m_mapPoint.emplace(m_iNaviPointIndex, m_pTempPoint);

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
		float YTemp = m_pMainCam->Get_Transform()->Get_Position().y;

		Vector3 vWorldPos = EngineFunction->Get_MainCamera()->Screen2World(m_vMousePos, YTemp);

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
				m_mapPoint.emplace(m_iNaviPointIndex, m_pTempPoint);
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


void NaviMeshTool_Dialog::OnBnClickedNavimeshsaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	//저장할때 필요한거 
	//1. 셀의 총개수
	//2. 한 셀의 세 점 위치.
	
	CFileDialog Dlg(FALSE,
		L"dat",
		L"",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"NaviMeshData(*.bin)|*.bin||", this);

	TCHAR	szDlg_First[256] = L"";
	GetCurrentDirectory(256, szDlg_First);
	PathRemoveFileSpec(szDlg_First);
	CString	 csResourcePath = szDlg_First;

	//상위폴더 두개 지워주기
	for (int i = 0; i < 1; ++i)
	{
		int pos = csResourcePath.ReverseFind('\\');
		csResourcePath = csResourcePath.Left(pos);
	}
	csResourcePath += L"/Resource/Data";
	Dlg.m_ofn.lpstrInitialDir = csResourcePath;

	if (Dlg.DoModal())
	{
		CString csFilePath = Dlg.GetPathName();

		HANDLE	hFile = CreateFile(csFilePath, GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		
		if (hFile == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(L"저장이 핸들 생성에서 실패 했읍니다. ㅅㄱ", MB_OK);
			return;
		}

		DWORD dwByte = 0;

		SaveInfo_NaviMesh NaviMeshSaveData;
		NaviMeshSaveData.Setting(m_iNaviPointIndex, m_iCellIndex);

		for (int i = 0; i < m_iNaviPointIndex; ++i)
		{
			NaviMeshSaveData.arrPointPosition[i] = m_mapPoint[i]->Get_Position();
		}

		vector<NaviCell*> tempCells = m_pNaviMesh->Get_NaivCellList();

		for (int i = 0; i < m_iCellIndex; ++i)
		{
			int iTemp[3];

			for (int j = 0; j < 3; ++j)
			{
				iTemp[j] = tempCells[i]->Get_NaviPoint(j)->Get_Index();
			}

			NaviMeshSaveData.arrCellPointIndex[i].x = (float)iTemp[0];
			NaviMeshSaveData.arrCellPointIndex[i].y = (float)iTemp[1];
			NaviMeshSaveData.arrCellPointIndex[i].z = (float)iTemp[2];
		}

	

		////저장할때 STL 쓰면안됨. STL도 하나의 클래스임.

		////NaviPoint Count
 	//	int iPointCount = m_iNaviPointIndex;
		////NaviPoint Position (역순으로...?)
		//vector<Vector3> vecPointPosition;

		//for (int i = 0; i < iPointCount; ++i)
		//{
		//	vecPointPosition.emplace_back(m_mapPoint[i]->Get_Position());
		//}

		////for (int i = iPointCount-1; i == 0 ; --i)
		////{
		////	vecPointPosition.emplace_back(m_mapPoint[i]);
		////}

		////CellCount
		//int iCellCount = m_iCellIndex;
		//vector<tuple<int, int, int>> vecCellPoint;

		//vector<NaviCell*> tempCells = m_pNaviMesh->Get_NaivCellList();

		//for (int i = 0; i < iCellCount; ++i)
		//{
		//	tuple<int, int, int> temp;
		//	
		//	int iTemp[3];

		//	for (int j = 0; j < 3; ++j)
		//	{
		//		iTemp[j]= tempCells[i]->Get_NaviPoint(j)->Get_Index();
		//	}

		//	temp = make_tuple(iTemp[0], iTemp[1], iTemp[2]);

		//	vecCellPoint.emplace_back(temp);
		//}

		////for (int i = iCellCount - 1; i == 0; --i)
		////{
		////	
		////}

		////NaviMeshSaveData.iPointCount = iPointCount;
		////NaviMeshSaveData.vecPointPosition = vecPointPosition;
		////NaviMeshSaveData.iCellCount = iCellCount;
		////NaviMeshSaveData.vecCellPoint = vecCellPoint;
		
		WriteFile(hFile, &NaviMeshSaveData.iPointCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < m_iNaviPointIndex; ++i)
		{
			WriteFile(hFile, &(NaviMeshSaveData.arrPointPosition[i]), sizeof(Vector3), &dwByte, nullptr);
		}
		WriteFile(hFile, &NaviMeshSaveData.iCellCount, sizeof(int), &dwByte, nullptr);
		for (int i = 0; i < m_iCellIndex; ++i)
		{
			WriteFile(hFile, &(NaviMeshSaveData.arrCellPointIndex[i]), sizeof(Vector3), &dwByte, nullptr);
		}


		Notice(L"냅이맷시 저장완료");

		CloseHandle(hFile);
	}



	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnBnClickedNavimeshloadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	CFileDialog Dlg(
		TRUE,
		nullptr,
		nullptr,
		OFN_OVERWRITEPROMPT,
		L".bin|*bin||",
		this);

	TCHAR	szDlg_First[256] = L"";
	GetCurrentDirectory(256, szDlg_First); //현재 문서 위치 받아오기
	PathRemoveFileSpec(szDlg_First); //맨 마지막 파일 이름 지움 -> 프로젝트 파일 있는 곳
	CString	 csDataFolderPath = szDlg_First;
	//상위폴더 두개 지워주기
	for (int i = 0; i < 1; ++i)
	{
		int pos = csDataFolderPath.ReverseFind('\\');
		csDataFolderPath = csDataFolderPath.Left(pos);
	}
	csDataFolderPath += L"/Resource/Data";
	Dlg.m_ofn.lpstrInitialDir = csDataFolderPath;


	if (Dlg.DoModal())
	{
		CString csFilePath = Dlg.GetPathName();

		HANDLE hFile = CreateFile(csFilePath, GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			AfxMessageBox(L"로드가 핸들 생성에서 실패했읍니다. ㅅㄱㅂ", MB_OK);
		}

		DWORD dwByte = 0;
		SaveInfo_NaviMesh LoadNaviMeshData;

		while (true)
		{
			//Point
			int iPointCount;
			ReadFile(hFile,
				&iPointCount,
				sizeof(int),
				&dwByte,
				nullptr);

			if (dwByte == 0)
			{
				break;
			}

			Vector3*		arrPointPosition = new Vector3[iPointCount];
			for (int i = 0; i < iPointCount; ++i)
			{
				ReadFile(hFile,
					&arrPointPosition[i],
					sizeof(Vector3),
					&dwByte,
					nullptr);
			}

			//Cell
			int iCellCount;
			ReadFile(hFile,
				&iCellCount,
				sizeof(int),
				&dwByte,
				nullptr);

			Vector3*		arrCellPointIndex = new Vector3[iCellCount];
			for (int i = 0; i < iCellCount; ++i)
			{
				ReadFile(hFile,
					&arrCellPointIndex[i],
					sizeof(Vector3),
					&dwByte,
					nullptr);
			}

			//setting
			LoadNaviMeshData.Setting(iPointCount, iCellCount);
			LoadNaviMeshData.arrPointPosition = arrPointPosition;
			LoadNaviMeshData.arrCellPointIndex = arrCellPointIndex;

			if (dwByte == 0)
			{
				break;
			}
		}

		//Create Points
		vector<NaviPoint*> vecPoint;
		for (int i = 0; i < LoadNaviMeshData.iPointCount; ++i)
		{
			NaviPoint* PointObject = Create_Sphere(LoadNaviMeshData.arrPointPosition[i], i);

			vecPoint.emplace_back(PointObject);

			m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());
			++m_iNaviPointIndex;
		}

		//CellSetting
		m_pNaviMesh = new NaviMesh;
		for (int i = 0; i < LoadNaviMeshData.iCellCount; ++i)
		{
 			NaviCell* Cell = new NaviCell;
			Cell->Set_CellIndex(i);
			Vector3		Index = LoadNaviMeshData.arrCellPointIndex[i];

			for (int j = 0; j < 3; ++j)
			{
				switch (j)
				{
				case 0:
				{Cell->Insert_NaviPoint(vecPoint[(int)Index.x], j); }
				break;

				case 1:
				{Cell->Insert_NaviPoint(vecPoint[(int)Index.y], j); }
				break;

				case 2:
				{Cell->Insert_NaviPoint(vecPoint[(int)Index.z], j); }
				break;

				default:
					break;
				}
				
			}

			Cell->Setup_Lines();
			
			
			m_pNaviMesh->Insert_NaviCell(Cell);
			m_pNaviMesh->Link_Cells();

			++m_iCellIndex;
		}

		AfxMessageBox(L"내비매쉬 로드 완료", MB_ICONASTERISK);
		CloseHandle(hFile);

	}



	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnLbnSelchangeListNavipointlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	m_iCurIndex = m_PointList.GetCurSel();
	
	m_pSelectPoint = m_mapPoint[m_iCurIndex];

	m_vPointPostion = m_pSelectPoint->Get_Position();
	



	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnEnChangeVerposxEdit()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	//if (m_pSelectPoint != nullptr)
	//{
	//	m_vPointPostion.x = (float)atof((CStringA)m_csPointPosX);

	//	m_pSelectPoint->Set_Position(m_vPointPostion);


	//	//m_pNaviMesh->Cells_Update();
	//}

	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnEnChangeVerposyEdit()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//if (m_pSelectPoint != nullptr)
	//{
	//	m_vPointPostion.y = (float)atof((CStringA)m_csPointPosY);

	//	m_pSelectPoint->Set_Position(m_vPointPostion);
	//	
	//	//m_pNaviMesh->Cells_Update();
	//}

	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnEnChangeVerposzEdit()
{
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	//if (m_pSelectPoint != nullptr)
	//{
	//	m_vPointPostion.z = (float)atof((CStringA)m_csPointPosZ);

	//	m_pSelectPoint->Set_Position(m_vPointPostion);
	//	
	//	//m_pNaviMesh->Cells_Update();
	//}

	UpdateData(FALSE);
}
