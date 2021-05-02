// NaviMeshTool_Dialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "NaviMeshTool_Dialog.h"
#include "afxdialogex.h"
#include "..\..\Engine\Header\Mesh_Renderer.h"


// NaviMeshTool_Dialog ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(NaviMeshTool_Dialog, CDialogEx)

NaviMeshTool_Dialog::NaviMeshTool_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NaviMesh_Dialog, pParent)

{

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


// NaviMeshTool_Dialog �޽��� ó�����Դϴ�.


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

	m_PointList.InsertString(m_iNaviPointIndex, to_wstring(m_iNaviPointIndex).c_str());
	
	++m_iNaviPointIndex;

	UpdateData(FALSE);
}


void NaviMeshTool_Dialog::OnBnClickedCheckPointcreate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	if (m_checkPointCreate.GetCheck())
	{//üũ �ȵ� ���� ��.
		m_checkPointCreate.SetCheck(true);
		m_bPointCreate = true;
	}
	else 
	{//üũ �� ���� ��.

		m_checkPointCreate.SetCheck(false);
		m_bPointCreate = false;
	}


	UpdateData(FALSE);
}
