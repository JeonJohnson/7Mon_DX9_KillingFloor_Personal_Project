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
END_MESSAGE_MAP()


// NaviMeshTool_Dialog 메시지 처리기입니다.


void NaviMeshTool_Dialog::OnBnClickedDeletevertexButton()
{
}

void NaviMeshTool_Dialog::Update_Info()
{
}

void NaviMeshTool_Dialog::Create_NaviPoint(const Vector3 & _WorldPos)
{
	UpdateData(TRUE);
	
	GameObject* pNaviPoint = INSTANTIATE(0, L"NaviPoint" + to_wstring(m_iNaviPointIndex));
	pNaviPoint->Set_Position(_WorldPos);

	Mesh_Renderer::Desc NaviPoint_Desc;
	NaviPoint_Desc.szMeshName = L"DebugSphere";
	pNaviPoint->Add_Component<Mesh_Renderer>(&NaviPoint_Desc);

	if (m_iNaviPointIndex < 3)
	{ //처음 3개 찍을때
		if (m_pTempCell == nullptr)
		{
			m_pTempCell = new NaviCell;
		}

		m_pTempPoint = new NaviPoint(_WorldPos);
		
		if (m_pTempCell->Get_PointArraySize() < 3)
		{
			m_pTempCell->Insert_NaviPoint(m_pTempPoint, m_iNaviPointIndex % 3);
			m_pTempCell->Setup_Lines();

			if (m_pTempCell->Get_PointArraySize() >= 3)
			{
				m_pNaviMesh->Insert_NaviCell(m_pTempCell);
				m_pTempCell = nullptr;
			}
			m_pTempPoint = nullptr;
		}		
	}
	else 
	{ //그외에 이제 2개 선택해서 찍어야 할 때.

	}



	m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());
	
	++m_iNaviPointIndex;

	UpdateData(FALSE);
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
